/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/26 16:17:40 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int draw_player(t_data *data)
{
    int x, y;
    int size = 10; // Size of the square

    for (y = data->player_y; y < data->player_y + size; y++)
    {
        for (x = data->player_x; x < data->player_x + size; x++)
        {
            mlx_pixel_put(data->mlx, data->win, x, y, GREEN);
        }
    }
    return 0;
}

int move_player(t_data *data, int keycode)
{
    int step = 10; // Step size for movement

    if (keycode == 65361) // Left arrow key
        data->player_x -= step;
    else if (keycode == 65362) // Up arrow key
        data->player_y -= step;
    else if (keycode == 65363) // Right arrow key
        data->player_x += step;
    else if (keycode == 65364) // Down arrow key
        data->player_y += step;

    // Clear the window and redraw the player at the new position
    mlx_clear_window(data->mlx, data->win);
    draw_player(data);

    return 0;
}