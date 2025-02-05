/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/05 19:12:14 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	draw_player(t_data *data)
{
	int x, y;
	int size = 10; // Size of the square
	y = data->player_y;
	while (y < data->player_y + size)
	{
		x = data->player_x;
		while (x < data->player_x + size)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, GREEN);
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
			start_x = x * BLOCK_SIZE + 1;
			start_y = y * BLOCK_SIZE + 1;
			end_x = start_x + BLOCK_SIZE - 1;
			end_y = start_y + BLOCK_SIZE - 1;
			i = start_y;
			while (i < end_y)
			{
				j = start_x;
				while (j < end_x)
				{
					mlx_pixel_put(data->mlx, data->win, j, i, color);
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

void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(data->mlx, data->win, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_direction(t_data *data)
{
    int ray_length = 100;
	
    int end_x = data->player_x + (data->player_d_x) * ray_length;
    int end_y = data->player_y + (data->player_d_y) * ray_length;
	
	// x + 5 && y + 5 to center the ray around player
    draw_line(data, data->player_x + 5, data->player_y + 5, end_x, end_y, GREEN);
}

// cast a ray based on player X and Y and check if it hit the wall every BLOCK_SIZE 
void cast_ray(t_data *data, float ray_angle)
{
    float ray_x = data->player_x;
    float ray_y = data->player_y;
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);
    int map_x, map_y;
    int hit = 0;

    while (!hit)
    {
        ray_x += ray_dx;
        ray_y += ray_dy;
        map_x = (int)(ray_x / BLOCK_SIZE);
        map_y = (int)(ray_y / BLOCK_SIZE);
        if (map_x >= 0 && map_x < data->map_x && map_y >= 0 && map_y < data->map_y)
        {
            if (data->map[map_y * data->map_x + map_x] == 1)
            {
                hit = 1; // 
				// x + 5 && y + 5 to center the ray around player	
                draw_line(data, data->player_x + 5, data->player_y + 5, ray_x, ray_y, RED);
            }
        }
        else
        {
            hit = 1;
        }
    }
}

void draw_rays(t_data *data)
{
    float fov = PI / 2; // Field of view (we use PI to represent the angle so instead of 360 we have PI * 2)
    float angle_step = fov / NUM_OF_RAYS;
    float start_angle = data->player_a - (fov / 2);

    for (int i = 0; i < NUM_OF_RAYS; i++)
    {
        float ray_angle = start_angle + i * angle_step;
        cast_ray(data, ray_angle);
    }
}
