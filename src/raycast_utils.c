/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 12:45:18 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 12:48:33 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static void	ray_dist_x(t_data *data, t_raycast *rc)
{
	if (rc->ray_dx < 0)
	{
		rc->x_step = -1;
		rc->side_dist_x = (data->player.x - rc->x_map * data->block_size)
			* rc->delta_dist_x / data->block_size;
	}
	else
	{
		rc->x_step = 1;
		rc->side_dist_x = ((rc->x_map + 1) * data->block_size
				- data->player.x) * rc->delta_dist_x / data->block_size;
	}
}

static void	init_raycast(t_data *data, t_ray_params *ray, t_raycast *rc)
{
	rc->ray_dx = cos(ray->ray_angle);
	rc->ray_dy = sin(ray->ray_angle);
	rc->x_map = (int)(data->player.x / data->block_size);
	rc->y_map = (int)(data->player.y / data->block_size);
	rc->delta_dist_x = fabsf(1 / rc->ray_dx);
	rc->delta_dist_y = fabsf(1 / rc->ray_dy);
	ray_dist_x(data, rc);
	if (rc->ray_dy < 0)
	{
		rc->y_step = -1;
		rc->side_dist_y = (data->player.y - rc->y_map * data->block_size)
			* rc->delta_dist_y / data->block_size;
	}
	else
	{
		rc->y_step = 1;
		rc->side_dist_y = ((rc->y_map + 1) * data->block_size
				- data->player.y) * rc->delta_dist_y / data->block_size;
	}
	rc->hit = 0;
}

static void	perform_dda(t_data *data, t_ray_params *ray, t_raycast *rc)
{
	while (!rc->hit)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->x_map += rc->x_step;
			ray->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->y_map += rc->y_step;
			ray->side = 1;
		}
		if (rc->x_map < 0 || rc->x_map >= data->map_x || rc->y_map < 0
			|| rc->y_map >= data->map_y || data->map[rc->y_map * data->map_x
				+ rc->x_map] == '1' || data->map[rc->y_map * data->map_x
				+ rc->x_map] == '2')
			rc->hit = 1;
	}
	if (rc->x_map >= 0 && rc->x_map < data->map_x && rc->y_map >= 0
		&& rc->y_map < data->map_y)
		ray->hit_cell = data->map[rc->y_map * data->map_x + rc->x_map];
	else
		ray->hit_cell = '1';
}

static float	calculate_distance(t_data *data, t_ray_params *ray,
		t_raycast *rc)
{
	if (ray->side == 0)
	{
		if (rc->x_step < 0)
			rc->distance = (rc->x_map * data->block_size - data->player.x
					+ data->block_size) / rc->ray_dx;
		else
			rc->distance = (rc->x_map * data->block_size - data->player.x)
				/ rc->ray_dx;
	}
	else
	{
		if (rc->y_step < 0)
			rc->distance = (rc->y_map * data->block_size - data->player.y
					+ data->block_size) / rc->ray_dy;
		else
			rc->distance = (rc->y_map * data->block_size - data->player.y)
				/ rc->ray_dy;
	}
	ray->hit_x = data->player.x + rc->distance * rc->ray_dx;
	ray->hit_y = data->player.y + rc->distance * rc->ray_dy;
	return (rc->distance * cos(ray->ray_angle - data->player.a));
}

float	cast_ray(t_data *data, t_ray_params *ray)
{
	t_raycast	raycast;

	init_raycast(data, ray, &raycast);
	perform_dda(data, ray, &raycast);
	return (calculate_distance(data, ray, &raycast));
}
