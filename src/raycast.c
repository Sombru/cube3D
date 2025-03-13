/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/13 11:54:44 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

t_ray_params	create_ray_params(float ray_angle)
{
	t_ray_params	params;

	params.ray_angle = ray_angle;
	params.side = 0;
	params.hit_x = 0;
	params.hit_y = 0;
	params.hit_cell = '0';
	return (params);
}

float	cast_ray(t_data *data, t_ray_params *ray)
{
	t_raycast	raycast;

	raycast.ray_dx = cos(ray->ray_angle);
	raycast.ray_dy = sin(ray->ray_angle);
	raycast.x_map = (int)(data->player.x / data->block_size);
	raycast.y_map = (int)(data->player.y / data->block_size);
	raycast.delta_dist_x = fabsf(1 / raycast.ray_dx);
	raycast.delta_dist_y = fabsf(1 / raycast.ray_dy);
	if (raycast.ray_dx < 0)
	{
		raycast.x_step = -1;
		raycast.side_dist_x = (data->player.x - raycast.x_map
				* data->block_size) * raycast.delta_dist_x / data->block_size;
	}
	else
	{
		raycast.x_step = 1;
		raycast.side_dist_x = ((raycast.x_map + 1) * data->block_size
				- data->player.x) * raycast.delta_dist_x / data->block_size;
	}
	if (raycast.ray_dy < 0)
	{
		raycast.y_step = -1;
		raycast.side_dist_y = (data->player.y - raycast.y_map
				* data->block_size) * raycast.delta_dist_y / data->block_size;
	}
	else
	{
		raycast.y_step = 1;
		raycast.side_dist_y = ((raycast.y_map + 1) * data->block_size
				- data->player.y) * raycast.delta_dist_y / data->block_size;
	}
	raycast.hit = 0;
	while (!raycast.hit)
	{
		if (raycast.side_dist_x < raycast.side_dist_y)
		{
			raycast.side_dist_x += raycast.delta_dist_x;
			raycast.x_map += raycast.x_step;
			ray->side = 0;
		}
		else
		{
			raycast.side_dist_y += raycast.delta_dist_y;
			raycast.y_map += raycast.y_step;
			ray->side = 1;
		}
		if (raycast.x_map < 0 || raycast.x_map >= data->map_x
			|| raycast.y_map < 0 || raycast.y_map >= data->map_y
			|| data->map[raycast.y_map * data->map_x + raycast.x_map] == '1'
			|| data->map[raycast.y_map * data->map_x + raycast.x_map] == '2')
			raycast.hit = 1;
	}
	if (raycast.x_map >= 0 && raycast.x_map < data->map_x && raycast.y_map >= 0
		&& raycast.y_map < data->map_y)
		ray->hit_cell = data->map[raycast.y_map * data->map_x + raycast.x_map];
	else
		ray->hit_cell = '1';
	if (ray->side == 0)
	{
		if (raycast.x_step < 0)
			raycast.distance = (raycast.x_map * data->block_size
					- data->player.x + data->block_size) / raycast.ray_dx;
		else
			raycast.distance = (raycast.x_map * data->block_size
					- data->player.x) / raycast.ray_dx;
	}
	else
	{
		if (raycast.y_step < 0)
			raycast.distance = (raycast.y_map * data->block_size
					- data->player.y + data->block_size) / raycast.ray_dy;
		else
			raycast.distance = (raycast.y_map * data->block_size
					- data->player.y) / raycast.ray_dy;
	}
	ray->hit_x = data->player.x + raycast.distance * raycast.ray_dx;
	ray->hit_y = data->player.y + raycast.distance * raycast.ray_dy;
	return (raycast.distance * cos(ray->ray_angle - data->player.a));
}

void	draw_rays(t_data *data)
{
	t_rays			rays;
	t_ray_params	ray;
	int				i;
	float			distance;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &rays.off_x, &rays.off_y);
	rays.start_angle = data->player.a - (PI / 6);
	rays.angle_step = (PI / 3) / NUM_OF_RAYS;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		rays.ray_angle = rays.start_angle + i * rays.angle_step;
		ray = create_ray_params(rays.ray_angle);
		distance = cast_ray(data, &ray);
		rays.screen_start_x = rays.off_x + (data->player.x * data->scaled_size
				/ data->block_size);
		rays.screen_start_y = rays.off_y + (data->player.y * data->scaled_size
				/ data->block_size);
		rays.screen_end_x = rays.off_x + (ray.hit_x * data->scaled_size
				/ data->block_size);
		rays.screen_end_y = rays.off_y + (ray.hit_y * data->scaled_size
				/ data->block_size);
		draw_line(data, line_coords(rays.screen_start_x, rays.screen_start_y,
				rays.screen_end_x, rays.screen_end_y), RED, 0);
		i++;
	}
}
