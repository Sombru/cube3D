/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/14 13:40:24 by nspalevi         ###   ########.fr       */
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

static void	draw_line_loop_3d(t_data *data, t_coord coord, int color, t_line *line)
{
	while (1)
	{
		pixel_to_frame_2d(data, coord.x0, coord.y0, color);
		if (coord.x0 == coord.x1 && coord.y0 == coord.y1)
			break ;
		line->e2 = line->err * 2;
		if (line->e2 > -line->dy)
		{
			line->err = line->err - line->dy;
			coord.x0 = coord.x0 + line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err = line->err + line->dx;
			coord.y0 = coord.y0 + line->sy;
		}
	}
}


static void	draw_line_loop_2d(t_data *data, t_coord coord, int color, t_line *line)
{
	while (1)
	{
		pixel_to_frame_2d(data, coord.x0, coord.y0, color);
		if (coord.x0 == coord.x1 && coord.y0 == coord.y1)
			break ;
		line->e2 = line->err * 2;
		if (line->e2 > -line->dy)
		{
			line->err = line->err - line->dy;
			coord.x0 = coord.x0 + line->sx;
		}
		if (line->e2 < line->dx)
		{
			line->err = line->err + line->dx;
			coord.y0 = coord.y0 + line->sy;
		}
	}
}

void	draw_line(t_data *data, t_coord coord, int color, int is_3d)
{
	t_line	line;

	line.dx = coord.x1 - coord.x0;
	if (line.dx < 0)
		line.dx = -line.dx;
	line.dy = coord.y1 - coord.y0;
	if (line.dy < 0)
		line.dy = -line.dy;
	if (coord.x0 < coord.x1)
		line.sx = 1;
	else
		line.sx = -1;
	if (coord.y0 < coord.y1)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx - line.dy;
	if (is_3d)
		draw_line_loop_3d(data, coord, color, &line);
	else
		draw_line_loop_2d(data, coord, color, &line);
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
	float	screen_start_x;
	float	screen_start_y;
	float	screen_end_x;
	float	screen_end_y;

	scale_block_size(data);
	get_map_offsets(data, data->scaled_size, &data->off_x, &data->off_y);
	screen_start_x = data->off_x + (data->player.x * data->scaled_size
			/ data->block_size);
	screen_start_y = data->off_y + (data->player.y * data->scaled_size
			/ data->block_size);
	screen_end_x = screen_start_x + (data->player.d_x * data->scaled_size);
	screen_end_y = screen_start_y + (data->player.d_y * data->scaled_size);
	draw_line(data, line_coords(screen_start_x, screen_start_y, screen_end_x,
			screen_end_y), GREEN, 0);
}
