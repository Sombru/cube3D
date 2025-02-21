/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/17 13:47:50 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// pixel_to_frame:
// Sets a pixel’s color at the specified (x, y) coordinate in either the 2D or 3D frame
// buffer by calculating the correct memory offset and writing the color value.
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

// draw_line:
// Draws a line between two given points on the frame buffer using Bresenham’s algorithm,
// which calculates the increments needed in both x and y directions and iterates until
// the destination is reached, setting pixels along the path.
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

// draw_player:
// Draws the player’s representation on the 2D map as a green square by calculating a
// centered square area around the player’s coordinate and filling it with green pixels.
int	draw_player(t_data *data)
{
	int	player_size;
	int	x;
	int	y;
	int	i;
	int	j;

	player_size = 10;
	x = (int)data->player_x - player_size / 2;
	y = (int)data->player_y - player_size / 2;
	i = 0;
	while (i < player_size)
	{
		j = 0;
		while (j < player_size)
		{
			pixel_to_frame(data, x + i, y + j, GREEN, 0);
			j = j + 1;
		}
		i = i + 1;
	}
	return (0);
}

// Iterates over the map grid, determines whether each cell represents a wall or floor
// space, then draws each cell as a block of pixels with the appropriate color on the 2D view.
int	draw_map(t_data *data)
{
	int	y;
	int	x;
	int	color;
	int	i;
	int	j;

	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y * data->map_x + x] == 1)
				color = WHITE;
			else
				color = BLACK;
			{
				i = 0;
				while (i < data->block_size)
				{
					j = 0;
					while (j < data->block_size)
					{
						pixel_to_frame(data, x * data->block_size + i, y
							* data->block_size + j, color, 0);
						j = j + 1;
					}
					i = i + 1;
				}
			}
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}

// draw_direction:
// Draws a short green line starting at the player’s position and extending in the direction
// the player is facing, providing a visual indicator of the player's facing direction.
void	draw_direction(t_data *data)
{
	int	line_length;
	int	x1;
	int	y1;

	line_length = 50;
	x1 = (int)(data->player_x + data->player_d_x * line_length);
	y1 = (int)(data->player_y + data->player_d_y * line_length);
	draw_line(data, (int)data->player_x, (int)data->player_y, x1, y1, GREEN, 0);
}
