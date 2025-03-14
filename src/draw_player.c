/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/14 14:20:10 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// pixel_to_frame() - Draws a single pixel
// to either 2D or 3D frame buffer at specified coordinates with given color
// draw_line() - Implements Bresenham's line algorithm
// to draw a line between two points
// scale_block_size() - Calculates scaled block size
// for minimap based on map dimensions
// get_map_offsets() - Calculates offsets to center minimap in window
// draw_map() - Renders the 2D minimap view showing
// walls, doors and empty spaces
// draw_player.) - Renders player.position as a small square on minimap
// draw_direction() - Draws line showing player.s viewing direction on minimap

static void	draw_line_loop(t_data *data, t_drawing *draw, int is_3d)
{
	int	x;
	int	y;

	x = draw->x0;
	y = draw->y0;
	while (1)
	{
		if (is_3d)
			pixel_to_frame_3d(data, x, y, draw->color);
		else
			pixel_to_frame_2d(data, x, y, draw->color);
		if (x == draw->x1 && y == draw->y1)
			break ;
		draw->e2 = draw->err * 2;
		if (draw->e2 > -draw->dy)
		{
			draw->err = draw->err - draw->dy;
			x += draw->sx;
		}
		if (draw->e2 < draw->dx)
		{
			draw->err = draw->err + draw->dx;
			y += draw->sy;
		}
	}
}

void	draw_line(t_data *data, t_coord coord, int color, int is_3d)
{
	t_drawing	draw;

	draw.x0 = coord.x0;
	draw.y0 = coord.y0;
	draw.x1 = coord.x1;
	draw.y1 = coord.y1;
	draw.color = color;
	draw.dx = draw.x1 - draw.x0;
	if (draw.dx < 0)
		draw.dx = -draw.dx;
	draw.dy = draw.y1 - draw.y0;
	if (draw.dy < 0)
		draw.dy = -draw.dy;
	if (draw.x0 < draw.x1)
		draw.sx = 1;
	else
		draw.sx = -1;
	if (draw.y0 < draw.y1)
		draw.sy = 1;
	else
		draw.sy = -1;
	draw.err = draw.dx - draw.dy;
	draw_line_loop(data, &draw, is_3d);
}

int	draw_player(t_data *data)
{
	t_draw	draw;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	draw.screen_x = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	draw.screen_y = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	data->player.size = data->scaled_size / 2;
	draw.i = -data->player.size / 2;
	while (draw.i < data->player.size / 2)
	{
		draw.j = -data->player.size / 2;
		while (draw.j < data->player.size / 2)
		{
			draw.px = draw.screen_x + draw.i;
			draw.py = draw.screen_y + draw.j;
			if (draw.px >= 0 && draw.px < data->minimap_size && draw.py >= 0
				&& draw.py < data->minimap_size)
				pixel_to_frame_2d(data, draw.px, draw.py, GREEN);
			draw.j++;
		}
		draw.i++;
	}
	return (0);
}

void	draw_direction(t_data *data)
{
	t_drawing	draw;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	draw.x0 = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	draw.y0 = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	draw.x1 = draw.x0 + (data->player.d_x * data->scaled_size);
	draw.y1 = draw.y0 + (data->player.d_y * data->scaled_size);
	draw_line(data, line_coords(draw.x0, draw.y0, draw.x1, draw.y1), GREEN, 0);
}
