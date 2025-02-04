/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/04 18:41:04 by pkostura         ###   ########.fr       */
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

t_ray draw_rays(t_data *data)
{
	t_ray *ray;
	float aTan;

	ray = malloc(sizeof(ray));
	ray->ray = 0;
	ray->ray_a = data->player_a;
	while (ray->ray < 1)
	{
		ray->dof = 0;
		aTan = -1/tan(ray->ray_a);
		if (ray->ray_a > PI)
		{
			ray->ray_y = ((data->player_y / 64) * 64) - 0.0001;
			ray->ray_x = (data->player_y - ray->ray_y) * aTan + data->player_x;
			ray->offset_y = -64;
			ray->offset_x = -ray->offset_y * aTan;
		}
		if (ray->ray < PI)
		{
			ray->ray_y = ((data->player_y / 64) * 64) + 64;
			ray->ray_x = (data->player_y - ray->ray_y) * aTan + data->player_x;
			ray->offset_y = 64;
			ray->offset_x = -ray->offset_y * aTan;
		}
		if (ray->ray_a == 0 || ray->ray_a == PI) // looking straight left or right
		{
			ray->ray_x = data->player_x;
			ray->ray_y = data->player_y;
			ray->dof = 8;
		}
		while (ray->dof < 8)
		{
			ray->map_x = ray->ray_x / 64;
			ray->map_y = ray->ray_y / 64;
			ray->map_hit = ray->map_y * data->map_x + ray->map_x;
			if(ray->map_hit * data->map_x * data->map_y && data->map[ray->map_hit] == 1)
				ray->dof = 8;
			else
			{
				ray->ray_x = ray->offset_x;
				ray->ray_y = ray->offset_y;
				ray->dof++;
			}
			
		}
		
	}
	
}
