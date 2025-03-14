/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/13 11:56:53 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// render_3D() - Creates the 3D view by casting rays and rendering textured wall slices with perspective correction

void	pixel_to_frame_2D(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_2d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	pixel_to_frame_3D(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_3d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	render_3D(t_data *data)
{
	int i = 0;
	data->angle_step = FOV / data->screen_width;
	data->start_angle = data->player.a - HALF_FOV;
	while (i < data->screen_width)
	{
		float ray_angle = data->start_angle + i * data->angle_step;
		int side;
		float hit_x, hit_y;
		char hit_cell;
		float distance = cast_ray(data, ray_angle, &side, &hit_x, &hit_y,
				&hit_cell);	
		if (distance < 0.001)
			distance = 0.001;
		float real_wall_height = (data->block_size * data->screen_height)
			/ distance;
		float unclamped_wall_start = (data->screen_height - real_wall_height)
			/ 2;
		int wall_height = (int)real_wall_height;
		if (wall_height > data->screen_height)
			wall_height = data->screen_height;
		int wall_start = (data->screen_height - wall_height) / 2;
		int wall_end = wall_start + wall_height;
		t_texture *tex;
		if (hit_cell == '2')
			tex = &data->door;
		else
		{
			if (side == 0)
			{
				if (cos(ray_angle) > 0)
					tex = &data->east;
				else
					tex = &data->west;
			}
			else
			{
				if (sin(ray_angle) > 0)
					tex = &data->south;
				else
					tex = &data->north;
			}
		}
		float hit_offset;
		if (side == 0)
			hit_offset = fmodf(hit_y, data->block_size);
		else
			hit_offset = fmodf(hit_x, data->block_size);
		int tex_x = (int)((hit_offset / data->block_size) * tex->width);
		if ((side == 0 && ray_angle > RIGHT_SIDE_START
				&& ray_angle < RIGHT_SIDE_END) || (side == 1 && ray_angle < PI))
			tex_x = tex->width - tex_x - 1;
		int y = 0;
		while (y < data->screen_height)
		{
			if (y < wall_start)
				pixel_to_frame_3D(data, i, y, BLUE);
			else if (y > wall_end)
				pixel_to_frame_3D(data, i, y, GREEN);
			else
			{
				float tex_pos = (y - unclamped_wall_start) / real_wall_height;
				int tex_y = (int)(tex_pos * tex->height);
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= tex->height)
					tex_y = tex->height - 1;
				int color = tex->data[tex_y * tex->width + tex_x];
				pixel_to_frame_3D(data, i, y, color);
			}
			y++;
		}
		i++;
	}
}
