/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:28:55 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/17 13:29:35 by nspalevi         ###   ########.fr       */
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

void	calculate_wall_dimensions(t_data *data, float distance,
		t_wall_dims *dims)
{
	dims->real_height = (data->block_size * data->screen_height) / distance;
	dims->start_unclamped = (data->screen_height - dims->real_height) / 2;
	dims->height = (int)dims->real_height;
	if (dims->height > data->screen_height)
		dims->height = data->screen_height;
	dims->start = (data->screen_height - dims->height) / 2;
	dims->end = dims->start + dims->height;
}

void	draw_wall_section(t_data *data, t_drawing *draw, int y)
{
	float	tex_pos;
	int		tex_y;
	int		color;

	if (y >= data->screen_height)
		return ;
	if (y < draw->wall_start)
		pixel_to_frame_3d(data, draw->x0, y, data->ceiling_color);
	else if (y > draw->wall_end)
		pixel_to_frame_3d(data, draw->x0, y, data->floor_color);
	else
	{
		tex_pos = (y - draw->start_unclamped) / draw->wall_height;
		tex_y = (int)(tex_pos * draw->tex->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= draw->tex->height)
			tex_y = draw->tex->height - 1;
		color = draw->tex->data[tex_y * draw->tex->width + draw->tex_x];
		pixel_to_frame_3d(data, draw->x0, y, color);
	}
	draw_wall_section(data, draw, y + 1);
}
