/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/13 11:06:07 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// cast_ray()
// - Implements DDA (Digital Differential Analysis) algorithm for raycasting,
// calculates wall hit positions and distances
// draw_rays() - Renders raycasting debug lines on minimap showing field of view

typedef struct s_raycast
{
	float	ray_dx;
	float	ray_dy;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	float	distance;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;
}			t_raycast;

float	cast_ray(t_data *data, float ray_angle, int *side, float *hit_x,
		float *hit_y, char *hit_cell)
{
	t_raycast	raycast;

	raycast.ray_dx = cos(ray_angle);
	raycast.ray_dy = sin(ray_angle);
	raycast.mapX = (int)(data->player.x / data->block_size);
	raycast.mapY = (int)(data->player.y / data->block_size);
	raycast.delta_dist_x = fabsf(1 / raycast.ray_dx);
	raycast.delta_dist_y = fabsf(1 / raycast.ray_dy);
	if (raycast.ray_dx < 0)
	{
		raycast.stepX = -1;
		raycast.side_dist_x = (data->player.x - raycast.mapX * data->block_size)
			* raycast.delta_dist_x / data->block_size;
	}
	else
	{
		raycast.stepX = 1;
		raycast.side_dist_x = ((raycast.mapX + 1) * data->block_size
				- data->player.x) * raycast.delta_dist_x / data->block_size;
	}
	if (raycast.ray_dy < 0)
	{
		raycast.stepY = -1;
		raycast.side_dist_y = (data->player.y - raycast.mapY * data->block_size)
			* raycast.delta_dist_y / data->block_size;
	}
	else
	{
		raycast.stepY = 1;
		raycast.side_dist_y = ((raycast.mapY + 1) * data->block_size
				- data->player.y) * raycast.delta_dist_y / data->block_size;
	}
	raycast.hit = 0;
	while (!raycast.hit)
	{
		if (raycast.side_dist_x < raycast.side_dist_y)
		{
			raycast.side_dist_x += raycast.delta_dist_x;
			raycast.mapX += raycast.stepX;
			*side = 0;
		}
		else
		{
			raycast.side_dist_y += raycast.delta_dist_y;
			raycast.mapY += raycast.stepY;
			*side = 1;
		}
		if (raycast.mapX < 0 || raycast.mapX >= data->map_x || raycast.mapY < 0
			|| raycast.mapY >= data->map_y || data->map[raycast.mapY
			* data->map_x + raycast.mapX] == '1' || data->map[raycast.mapY
			* data->map_x + raycast.mapX] == '2')
			raycast.hit = 1;
	}
	if (raycast.mapX >= 0 && raycast.mapX < data->map_x && raycast.mapY >= 0
		&& raycast.mapY < data->map_y)
		*hit_cell = data->map[raycast.mapY * data->map_x + raycast.mapX];
	else
		*hit_cell = '1';
	if (*side == 0)
	{
		if (raycast.stepX < 0)
			raycast.distance = (raycast.mapX * data->block_size - data->player.x
					+ data->block_size) / raycast.ray_dx;
		else
			raycast.distance = (raycast.mapX * data->block_size
					- data->player.x) / raycast.ray_dx;
	}
	else
	{
		if (raycast.stepY < 0)
			raycast.distance = (raycast.mapY * data->block_size - data->player.y
					+ data->block_size) / raycast.ray_dy;
		else
			raycast.distance = (raycast.mapY * data->block_size
					- data->player.y) / raycast.ray_dy;
	}
	*hit_x = data->player.x + raycast.distance * raycast.ray_dx;
	*hit_y = data->player.y + raycast.distance * raycast.ray_dy;
	return (raycast.distance * cos(ray_angle - data->player.a));
}

typedef struct s_rays
{
	float	start_angle;
	float	angle_step;
	float	ray_angle;
	float	screen_start_x;
	float	screen_start_y;
	float	screen_end_x;
	float	screen_end_y;
	float	hit_x;
	float	hit_y;
	int		side;
	int		off_y;
	int		off_x;
	char	hit_cell;
}			t_rays;

void	draw_rays(t_data *data)
{
	t_rays	rays;
	int		i;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &rays.off_x, &rays.off_y);
	rays.start_angle = data->player.a - (PI / 6);
	rays.angle_step = (PI / 3) / NUM_OF_RAYS;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		rays.ray_angle = rays.start_angle + i * rays.angle_step;
		cast_ray(data, rays.ray_angle, &rays.side, &rays.hit_x, &rays.hit_y,
			&rays.hit_cell);
		rays.screen_start_x = rays.off_x + (data->player.x * data->scaled_size
				/ data->block_size);
		rays.screen_start_y = rays.off_y + (data->player.y * data->scaled_size
				/ data->block_size);
		rays.screen_end_x = rays.off_x + (rays.hit_x * data->scaled_size
				/ data->block_size);
		rays.screen_end_y = rays.off_y + (rays.hit_y * data->scaled_size
				/ data->block_size);
		draw_line(data,  line_coords(rays.screen_start_x, rays.screen_start_y,
			rays.screen_end_x, rays.screen_end_y), RED, 0);
		i++;
	}
}
