/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/17 13:53:54 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

t_ray	create_ray(float ray_angle)
{
	t_ray	ray;

	ray.ray_angle = ray_angle;
	ray.side = 0;
	ray.hit_x = 0;
	ray.hit_y = 0;
	ray.hit_cell = '0';
	return (ray);
}

static void	draw_single_ray(t_data *data, t_ray *ray, int ray_index)
{
	ray->ray_angle = data->start_angle + ray_index * data->angle_step;
	*ray = create_ray(ray->ray_angle);
	cast_ray(data, ray);
	ray->screen_start_x = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	ray->screen_start_y = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	ray->screen_end_x = data->off_x + (ray->hit_x * data->scaled_size
			/ data->block_size);
	ray->screen_end_y = data->off_y + (ray->hit_y * data->scaled_size
			/ data->block_size);
	draw_line(data, line_coords(ray->screen_start_x, ray->screen_start_y,
			ray->screen_end_x, ray->screen_end_y), RED, 0);
}

void	draw_rays(t_data *data)
{
	t_ray	ray;
	int		i;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	if (NUM_OF_RAYS > 0)
		data->angle_step = FOV / NUM_OF_RAYS;
	else
		data->angle_step = FOV;
	data->start_angle = data->player.a - HALF_FOV;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		draw_single_ray(data, &ray, i);
		i++;
	}
}
