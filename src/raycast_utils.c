/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:45:18 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 14:14:09 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static void	ray_dist_x(t_data *data, t_ray *ray)
{
	if (ray->ray_dx < 0)
	{
		ray->x_step = -1;
		ray->side_dist_x = (data->player.x - ray->x_map * data->block_size)
			* ray->delta_dist_x / data->block_size;
	}
	else
	{
		ray->x_step = 1;
		ray->side_dist_x = ((ray->x_map + 1) * data->block_size
				- data->player.x) * ray->delta_dist_x / data->block_size;
	}
}

static void	init_raycast(t_data *data, t_ray *ray)
{
	ray->ray_dx = cos(ray->ray_angle);
	ray->ray_dy = sin(ray->ray_angle);
	ray->x_map = (int)(data->player.x / data->block_size);
	ray->y_map = (int)(data->player.y / data->block_size);
	ray->delta_dist_x = fabsf(1 / ray->ray_dx);
	ray->delta_dist_y = fabsf(1 / ray->ray_dy);
	ray_dist_x(data, ray);
	if (ray->ray_dy < 0)
	{
		ray->y_step = -1;
		ray->side_dist_y = (data->player.y - ray->y_map * data->block_size)
			* ray->delta_dist_y / data->block_size;
	}
	else
	{
		ray->y_step = 1;
		ray->side_dist_y = ((ray->y_map + 1) * data->block_size
				- data->player.y) * ray->delta_dist_y / data->block_size;
	}
	ray->hit = 0;
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->x_map += ray->x_step;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->y_map += ray->y_step;
			ray->side = 1;
		}
		if (ray->x_map < 0 || ray->x_map >= data->map_x || ray->y_map < 0
			|| ray->y_map >= data->map_y || data->map[ray->y_map * data->map_x
				+ ray->x_map] == '1' || data->map[ray->y_map * data->map_x
				+ ray->x_map] == '2')
			ray->hit = 1;
	}
	if (ray->x_map >= 0 && ray->x_map < data->map_x && ray->y_map >= 0
		&& ray->y_map < data->map_y)
		ray->hit_cell = data->map[ray->y_map * data->map_x + ray->x_map];
	else
		ray->hit_cell = '1';
}

static float	calculate_distance(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->x_step < 0)
			ray->distance = (ray->x_map * data->block_size - data->player.x
					+ data->block_size) / ray->ray_dx;
		else
			ray->distance = (ray->x_map * data->block_size - data->player.x)
				/ ray->ray_dx;
	}
	else
	{
		if (ray->y_step < 0)
			ray->distance = (ray->y_map * data->block_size - data->player.y
					+ data->block_size) / ray->ray_dy;
		else
			ray->distance = (ray->y_map * data->block_size - data->player.y)
				/ ray->ray_dy;
	}
	ray->hit_x = data->player.x + ray->distance * ray->ray_dx;
	ray->hit_y = data->player.y + ray->distance * ray->ray_dy;
	return (ray->distance * cos(ray->ray_angle - data->player.a));
}

float	cast_ray(t_data *data, t_ray *ray)
{
	init_raycast(data, ray);
	perform_dda(data, ray);
	return (calculate_distance(data, ray));
}
