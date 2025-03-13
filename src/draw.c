/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/13 09:52:38 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// pixel_to_frame() - Draws a single pixel to either 2D or 3D frame buffer at specified coordinates with given color
// draw_line() - Implements Bresenham's line algorithm to draw a line between two points
// scale_block_size() - Calculates scaled block size for minimap based on map dimensions
// get_map_offsets() - Calculates offsets to center minimap in window
// draw_map() - Renders the 2D minimap view showing walls, doors and empty spaces
// draw_player.) - Renders player.position as a small square on minimap
// draw_direction() - Draws line showing player.s viewing direction on minimap

void	pixel_to_frame(t_data *data, int x, int y, int color, int is_3d)
{
	char	*dst;

	if (is_3d != 0)
		dst = data->addr_3d + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
	else
		dst = data->addr_2d + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color,
		int is_3d)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = x1 - x0;
	if (dx < 0)
		dx = -dx;
	dy = y1 - y0;
	if (dy < 0)
		dy = -dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		pixel_to_frame(data, x0, y0, color, is_3d);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}

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
						pixel_to_frame(data, px + i, py + j, color, 0);
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

int	draw_player(t_data *data)
{
	float	screen_x;
	float	screen_y;
	int		i;
	int		j;
	int		px;
	int		py;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	screen_x = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	screen_y = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	data->player.size = data->scaled_size / 2;
	i = -data->player.size / 2;
	while (i < data->player.size / 2)
	{
		j = -data->player.size / 2;
		while (j < data->player.size / 2)
		{
			px = screen_x + i;
			py = screen_y + j;
			if (px >= 0 && px < data->minimap_size && py >= 0
				&& py < data->minimap_size)
				pixel_to_frame(data, px, py, GREEN, 0);
			j++;
		}
		i++;
	}
	return (0);
}

void	draw_direction(t_data *data)
{
	float screen_start_x;
	float screen_start_y;
	float screen_end_x;
	float screen_end_y;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	screen_start_x = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	screen_start_y = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	screen_end_x = screen_start_x + (data->player.d_x * data->scaled_size);
	screen_end_y = screen_start_y + (data->player.d_y * data->scaled_size);
	draw_line(data, screen_start_x, screen_start_y, screen_end_x, screen_end_y,
		GREEN, 0);
}
