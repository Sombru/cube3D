/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/08 16:02:56 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	pixel_to_frame(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_player(t_data *data)
{
	int x, y;
	int size = 10; // Size of the player
	y = data->player_y;
	while (y < data->player_y + size)
	{
		x = data->player_x;
		while (x < data->player_x + size)
		{
			pixel_to_frame(data, x, y, GREEN);
			x++;		
		}
		y++;
	}
	return (0);
}

int	draw_map(t_data *data)
{
	int	color;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	i;
	int	j;

	int x, y;
	y = 0;
	while (y < data->map_y)
	{
		x = 0;
		while (x < data->map_x)
		{
			if (data->map[y * data->map_x + x] == 1)
				color = WHITE; // Wall
			else
				color = BLACK; // Empty space
			start_x = x * data->block_size + 1;
			start_y = y * data->block_size + 1;
			end_x = start_x + data->block_size - 1;
			end_y = start_y + data->block_size - 1;
			i = start_y;
			while (i < end_y)
			{
				j = start_x;
				while (j < end_x)
				{
					pixel_to_frame(data, j, i, color);
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
// https://www.youtube.com/watch?v=CceepU1vIKo&t=18s
// we use abs of x0, x1 and y0, y1 to get absolute diference in coordinates
void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
	int	D2;

	delta_x = abs(x1 - x0);
	delta_y = abs(y1 - y0);
	int D = delta_x - delta_y;
		// D is to increment or decrement x anb y coordinates
	if (x0 < x1)
		step_x = 1;
	else
		step_x = -1;
	if (y0 < y1)
		step_y = 1;
	else
		step_y = -1;
	while (1)
	{
		pixel_to_frame(data, x0, y0, color);
		if (x0 == x1 && y0 == y1) // draw line until x0, x1, reaches y0, y1
			break ;
		D2 = D * 2;
		if (D2 > -delta_y)
		{
			D -= delta_y;
			x0 += step_x;
		}
		if (D2 < delta_x)
		{
			D += delta_x;
			y0 += step_y;
		}
	}
}

void	draw_direction(t_data *data)
{
	int	ray_length;
	int	end_x;
	int	end_y;

	ray_length = 100;
	end_x = data->player_x + (data->player_d_x) * ray_length;
	end_y = data->player_y + (data->player_d_y) * ray_length;
	// x + 5 && y + 5 to center the ray around player
	draw_line(data, data->player_x + 5, data->player_y + 5, end_x, end_y,
		GREEN);
}

// cast a ray based on player X and Y and check if it hit the wall every block_size
void	cast_ray(t_data *data, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	ray_dx;
	float	ray_dy;
	int		hit;

	ray_x = data->player_x;
	ray_y = data->player_y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	int map_x, map_y;
	hit = 0;
	while (!hit)
	{
		ray_x += ray_dx;
		ray_y += ray_dy;
		map_x = (int)(ray_x / data->block_size);
		map_y = (int)(ray_y / data->block_size);
		if (map_x >= 0 && map_x < data->map_x && map_y >= 0
			&& map_y < data->map_y)
		{
			if (data->map[map_y * data->map_x + map_x] == 1)
			{
				hit = 1; //
							// x + 5 && y + 5 to center the ray around player
				draw_line(data, data->player_x + 5, data->player_y + 5, ray_x,
					ray_y, RED);
			}
		}
		else
			hit = 1;
	}
}

// fov of 360 would be 2PI since machie uses it instead of 360
// 360 = 2PI, 180 = PI, 90 = PI/2, etc..

void	draw_rays(t_data *data)
{
	float	fov;
	float	angle_step;
	float	start_angle;
	float	ray_angle;
	int		i;

	fov = PI / 2;
	angle_step = fov / NUM_OF_RAYS;
	start_angle = data->player_a - (fov / 2);
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		cast_ray(data, ray_angle);
		i++;
	}
}
