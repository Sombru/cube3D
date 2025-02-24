/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/02/24 13:59:06 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

float	cast_ray(t_data *data, float ray_angle, int *side, float *hit_x,
		float *hit_y, char *hit_cell)
{
	float	ray_dx;
	float	ray_dy;
	int		mapX;
	int		mapY;
	float	delta_dist_x;
	float	delta_dist_y;
	int		stepX;
	int		stepY;
	float	side_dist_x;
	float	side_dist_y;
	int		hit;
	float	distance;

	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	mapX = (int)(data->player_x / data->block_size);
	mapY = (int)(data->player_y / data->block_size);
	delta_dist_x = fabsf(1 / ray_dx);
	delta_dist_y = fabsf(1 / ray_dy);
	if (ray_dx < 0)
		stepX = -1;
	else
		stepX = 1;
	if (ray_dy < 0)
		stepY = -1;
	else
		stepY = 1;
	if (ray_dx < 0)
		side_dist_x = (data->player_x - mapX * data->block_size) * delta_dist_x
			/ data->block_size;
	else
		side_dist_x = ((mapX + 1) * data->block_size - data->player_x)
			* delta_dist_x / data->block_size;
	if (ray_dy < 0)
		side_dist_y = (data->player_y - mapY * data->block_size) * delta_dist_y
			/ data->block_size;
	else
		side_dist_y = ((mapY + 1) * data->block_size - data->player_y)
			* delta_dist_y / data->block_size;
	hit = 0;
	while (!hit) // DDA
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			mapX += stepX;
			*side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			mapY += stepY;
			*side = 1;
		}
		if (mapX < 0 || mapX >= data->map_x || mapY < 0 || mapY >= data->map_y)
			hit = 1;
		else if (data->map[mapY * data->map_x + mapX] == '1' || data->map[mapY
			* data->map_x + mapX] == '2')
			hit = 1;
	}
	if (mapX >= 0 && mapX < data->map_x && mapY >= 0 && mapY < data->map_y)
		*hit_cell = data->map[mapY * data->map_x + mapX];
	else
		*hit_cell = '1';
	if (*side == 0)
	{
		if (stepX < 0)
			distance = (mapX * data->block_size - data->player_x
					+ data->block_size) / ray_dx;
		else
			distance = (mapX * data->block_size - data->player_x) / ray_dx;
	}
	else
	{
		if (stepY < 0)
			distance = (mapY * data->block_size - data->player_y
					+ data->block_size) / ray_dy;
		else
			distance = (mapY * data->block_size - data->player_y) / ray_dy;
	}
	*hit_x = data->player_x + distance * ray_dx;
	*hit_y = data->player_y + distance * ray_dy;
	return (distance * cos(ray_angle - data->player_a));
}

void	draw_rays(t_data *data)
{
	float start_angle;
	float angle_step;
	int i;
	float ray_angle;
	int side;
	char hit_cell;
	float screen_start_x;
	float screen_start_y;
	float screen_end_x;
	float screen_end_y;

	int off_x, off_y;
	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &off_x, &off_y);
	start_angle = data->player_a - (PI / 6);
	angle_step = (PI / 3) / NUM_OF_RAYS;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		float hit_x, hit_y;
		cast_ray(data, ray_angle, &side, &hit_x, &hit_y, &hit_cell);
		screen_start_x = off_x + (data->player_x * data->scaled_size
				/ data->block_size);
		screen_start_y = off_y + (data->player_y * data->scaled_size
				/ data->block_size);
		screen_end_x = off_x + (hit_x * data->scaled_size / data->block_size);
		screen_end_y = off_y + (hit_y * data->scaled_size / data->block_size);
		draw_line(data, screen_start_x, screen_start_y, screen_end_x,
			screen_end_y, RED, 0);
		i++;
	}
}