/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:15 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/13 10:49:24 by pkostura         ###   ########.fr       */
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

int	draw_map(t_data *data)
{
	int	x;
	int	y;
	int	px;
	int	py;
	int	i;
	int	j;
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
				color = RED;
			else
				color = BLACK;
			px = data->off_x + (x * data->scaled_size);
			py = data->off_y + (y * data->scaled_size);
			i = 0;
			while (i < data->scaled_size)
			{
				j = 0;
				while (j < data->scaled_size)
				{
					if (px + i < data->minimap_size && py
						+ j < data->minimap_size)
						pixel_to_frame_2D(data, px + i, py + j, color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
	return (0);
}
