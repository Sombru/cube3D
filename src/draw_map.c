/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:15 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/20 08:03:53 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	scale_block_size(t_data *data)
{
	int	max_dim;

	if (data->map_x > data->map_y)
		max_dim = data->map_x;
	else
		max_dim = data->map_y;
	data->scaled_size = data->minimap_size / max_dim;
	return (data->scaled_size);
}

void	get_map_offsets(t_data *data, int block_size, int *off_x, int *off_y)
{
	*off_x = (data->minimap_size - (data->map_x * block_size)) / 2;
	*off_y = (data->minimap_size - (data->map_y * block_size)) / 2;
}

static void	draw_block(t_data *data, int x, int y, int color)
{
	t_drawing	draw;
	int			i;
	int			j;

	draw.x0 = data->off_x + (x * data->scaled_size);
	draw.y0 = data->off_y + (y * data->scaled_size);
	draw.color = color;
	i = 0;
	while (i < data->scaled_size)
	{
		j = 0;
		while (j < data->scaled_size)
		{
			if (draw.x0 + i < data->minimap_size && draw.y0
				+ j < data->minimap_size)
				pixel_to_frame_2d(data, draw.x0 + i, draw.y0 + j, draw.color);
			j++;
		}
		i++;
	}
}

int	draw_map(t_data *data)
{
	int	x;
	int	y;
	int	color;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y * data->map_x + x] == '1')
				color = WHITE;
			else if (data->map[y * data->map_x + x] == '2')
				color = PURPLE;
			else
				color = BLACK;
			draw_block(data, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}
