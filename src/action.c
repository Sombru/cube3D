/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/26 17:07:16 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int action(t_data *data, int keycode)
{
    int step = 10; // Step size for movement

    if (keycode == LEFT_ARROW) // Left arrow key
        data->player_x -= step;
    else if (keycode == UP_ARROW) // Up arrow key
        data->player_y -= step;
    else if (keycode == RIGHT_ARROW) // Right arrow key
        data->player_x += step;
    else if (keycode == DOWN_ARROW) // Down arrow key
        data->player_y += step;
	else if (keycode == ESCAPE)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit (0);
	}

    // Clear the window and redraw the player at the new position
    mlx_clear_window(data->mlx, data->win);
    draw_player(data);

    return 0;
}