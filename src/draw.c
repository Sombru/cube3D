/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/29 10:51:23 by pkostura         ###   ########.fr       */
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
	int cell_size;
	
	cell_size = 50;
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
			start_x = x * cell_size-1;
			start_y = y * cell_size-1;
			end_x = start_x + cell_size-1;
			end_y = start_y + cell_size-1;
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
