/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/13 11:19:59 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	render_3D(t_data *data)
{
	int				i;
	float			ray_angle;
	int				side;
	char			hit_cell;
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
	float			hit_x;
	float			hit_y;

	i = 0;
	data->angle_step = FOV / data->screen_width;
	data->start_angle = data->player.a - HALF_FOV;
	while (i < data->screen_width)
	{
		ray_angle = data->start_angle + i * data->angle_step;
		distance = cast_ray(data, ray_angle, &side, &hit_x, &hit_y, &hit_cell);
		if (distance < 0.001)
			distance = 0.001;
		real_wall_height = (data->block_size * data->screen_height) / distance;
		unclamped_wall_start = (data->screen_height - real_wall_height) / 2;
		wall_height = (int)real_wall_height;
		if (wall_height > data->screen_height)
			wall_height = data->screen_height;
		wall_start = (data->screen_height - wall_height) / 2;
		wall_end = wall_start + wall_height;
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
		if (side == 0)
			hit_offset = fmodf(hit_y, data->block_size);
		else
			hit_offset = fmodf(hit_x, data->block_size);
		tex_x = (int)((hit_offset / data->block_size) * tex->width);
		if ((side == 0 && ray_angle > RIGHT_SIDE_START
				&& ray_angle < RIGHT_SIDE_END) || (side == 1 && ray_angle < PI))
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
				tex_pos = (y - unclamped_wall_start) / real_wall_height;
				tex_y = (int)(tex_pos * tex->height);
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= tex->height)
					tex_y = tex->height - 1;
				color = tex->data[tex_y * tex->width + tex_x];
				pixel_to_frame(data, i, y, color, 1);
			}
			y++;
		}
		i++;
	}
}
