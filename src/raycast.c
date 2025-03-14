/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:08:23 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 12:45:15 by nspalevi         ###   ########.fr       */
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

static void	draw_single_ray(t_data *data, t_rays *rays, int ray_index)
{
	t_ray_params	ray;

	rays->ray_angle = rays->start_angle + ray_index * rays->angle_step;
	ray = create_ray_params(rays->ray_angle);
	cast_ray(data, &ray);
	rays->screen_start_x = rays->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	rays->screen_start_y = rays->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	rays->screen_end_x = rays->off_x + (ray.hit_x * data->scaled_size
			/ data->block_size);
	rays->screen_end_y = rays->off_y + (ray.hit_y * data->scaled_size
			/ data->block_size);
	draw_line(data, line_coords(rays->screen_start_x, rays->screen_start_y,
			rays->screen_end_x, rays->screen_end_y), RED, 0);
}

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
		draw_single_ray(data, &rays, i);
		i++;
	}
}
