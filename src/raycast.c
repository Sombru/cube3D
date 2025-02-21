/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/02/21 18:16:32 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// cast_ray:
// Casts a single ray from the player’s position using DDA,
// determining the point of impact with a wall on the map, computing the hit point, 
// and returning the corrected distance (with fish-eye correction) for that ray.

// dda_algorithm: Implements the Digital Differential Analyzer (DDA) algorithm for ray traversal.
// Starting at the player's position, it computes incremental steps along the ray's x and y directions based on the ray's cosine and sine values.
// In each iteration, the algorithm determines whether to step in the x or y direction by comparing the accumulated distances.
// It continues these incremental steps until a wall is encountered in the map,
// thereby identifying the precise intersection point and distance along the ray.
float	cast_ray(t_data *data, float ray_angle, int *side, float *hit_x,
		float *hit_y)
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
	while (hit == 0) // DDA
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x = side_dist_x + delta_dist_x;
			mapX = mapX + stepX;
			*side = 0;
		}
		else
		{
			side_dist_y = side_dist_y + delta_dist_y;
			mapY = mapY + stepY;
			*side = 1;
		}
		if (mapX < 0 || mapX >= data->map_x || mapY < 0 || mapY >= data->map_y
			|| data->map[mapY * data->map_x + mapX] == '1')
		{
			hit = 1;
		}
	}
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

// draw_rays:
// Iterates over a number of rays spread across the field of view, casts each ray,
// and draws a line representing the ray on the 2D view from the player to the hit point.
void	draw_rays(t_data *data)
{
	float	start_angle;
	float	angle_step;
	int		i;
	float	ray_angle;
	int		side;
	float	hit_x;
	float	hit_y;

	start_angle = data->player_a - (PI / 6);
	angle_step = (PI / 3) / NUM_OF_RAYS;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		cast_ray(data, ray_angle, &side, &hit_x, &hit_y);
		draw_line(data, (int)data->player_x, (int)data->player_y, (int)hit_x,
			(int)hit_y, RED, 0);
		i = i + 1;
	}
}
