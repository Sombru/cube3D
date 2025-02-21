/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/02/21 19:38:40 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// render_3D:
// Renders the 3D view by casting rays across the field of view, calculating wall
// distances and heights, selecting the correct texture slice based on hit data,
// and drawing vertical columns for the scene.
void	render_3D(t_data *data)
{
	float angle_step;
	float start_angle;
	int i;

	angle_step = FOV / data->screen_width;
	start_angle = data->player_a - HALF_FOV;
	i = 0;
	while (i < data->screen_width)
	{
		float ray_angle;
		int side;
		float hit_x;
		float hit_y;
		float distance;
		int wall_height;
		int wall_start;
		int wall_end;
		float hit_offset;
		int tex_x;
		int y;
		t_texture *tex;
		float ray_dx;
		float ray_dy;

		ray_angle = start_angle + i * angle_step;
		distance = cast_ray(data, ray_angle, &side, &hit_x, &hit_y);
		if (distance < 0.001)
			distance = 0.001;
		wall_height = (int)((data->block_size * data->screen_height)
				/ distance);
		if (wall_height > data->screen_height)
			wall_height = data->screen_height;
		wall_start = (data->screen_height - wall_height) / 2;
		wall_end = wall_start + wall_height;
		ray_dx = cos(ray_angle);
		ray_dy = sin(ray_angle);
		if (side == 0)
		{
			if (ray_dx > 0)
				tex = &data->east;
			else
				tex = &data->west;
		}
		else
		{
			if (ray_dy > 0)
				tex = &data->south;
			else
				tex = &data->north;
		}
		if (side == 0)
			hit_offset = fmodf(hit_y, data->block_size);
		else
			hit_offset = fmodf(hit_x, data->block_size);
		tex_x = (int)((hit_offset / data->block_size) * tex->width);
		if (side == 0 && ray_angle > RIGHT_SIDE_START
			&& ray_angle < RIGHT_SIDE_END)
			tex_x = tex->width - tex_x - 1;
		else if (side == 1 && ray_angle < PI)
			tex_x = tex->width - tex_x - 1;
		y = 0;
		while (y < data->screen_height)
		{
			if (y < wall_start)
				pixel_to_frame(data, i, y, BLUE, 1);
			else if (y > wall_end)
				pixel_to_frame(data, i, y, GREEN, 1);
			else
			{
				int d;
				int tex_y;
				int color;
				d = (y - wall_start) * tex->height / wall_height;
				tex_y = d;
				color = tex->data[tex_y * tex->width + tex_x];
				pixel_to_frame(data, i, y, color, 1);
			}
			y = y + 1;
		}
		i = i + 1;
	}
}