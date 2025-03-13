/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/13 11:57:04 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	pixel_to_frame_2d(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_2d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	pixel_to_frame_3d(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_3d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	render_3D(t_data *data)
{
	int				i;
	t_ray_params	ray;
	float			distance;
	float			real_wall_height;
	float			unclamped_wall_start;
	int				wall_height;
	int				wall_start;
	int				wall_end;
	t_texture		*tex;
	float			hit_offset;
	int				tex_x;
	int				y;
	float			tex_pos;
	int				tex_y;
	int				color;

	i = 0;
	data->angle_step = FOV / data->screen_width;
	data->start_angle = data->player.a - HALF_FOV;
	while (i < data->screen_width)
	{
		ray = create_ray_params(data->start_angle + i * data->angle_step);
		distance = cast_ray(data, &ray);
		if (distance < 0.001)
			distance = 0.001;
		real_wall_height = (data->block_size * data->screen_height) / distance;
		unclamped_wall_start = (data->screen_height - real_wall_height) / 2;
		wall_height = (int)real_wall_height;
		if (wall_height > data->screen_height)
			wall_height = data->screen_height;
		wall_start = (data->screen_height - wall_height) / 2;
		wall_end = wall_start + wall_height;
		if (ray.hit_cell == '2')
			tex = &data->door;
		else
		{
			if (ray.side == 0)
			{
				if (cos(ray.ray_angle) > 0)
					tex = &data->east;
				else
					tex = &data->west;
			}
			else
			{
				if (sin(ray.ray_angle) > 0)
					tex = &data->south;
				else
					tex = &data->north;
			}
		}
		if (ray.side == 0)
			hit_offset = fmodf(ray.hit_y, data->block_size);
		else
			hit_offset = fmodf(ray.hit_x, data->block_size);
		tex_x = (int)((hit_offset / data->block_size) * tex->width);
		if ((ray.side == 0 && ray.ray_angle > RIGHT_SIDE_START
				&& ray.ray_angle < RIGHT_SIDE_END) || (ray.side == 1
				&& ray.ray_angle < PI))
			tex_x = tex->width - tex_x - 1;
		y = 0;
		while (y < data->screen_height)
		{
			if (y < wall_start)
				pixel_to_frame_3d(data, i, y, BLUE);
			else if (y > wall_end)
				pixel_to_frame_3d(data, i, y, GREEN);
			else
			{
				tex_pos = (y - unclamped_wall_start) / real_wall_height;
				tex_y = (int)(tex_pos * tex->height);
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= tex->height)
					tex_y = tex->height - 1;
				color = tex->data[tex_y * tex->width + tex_x];
				pixel_to_frame_3d(data, i, y, color);
			}
			y++;
		}
		i++;
	}
}