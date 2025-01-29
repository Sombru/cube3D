/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/27 11:01:38 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int action(int keycode, t_data *data)
{
    int step = 10; // Step size for movement

    if (keycode == LEFT_ARROW || keycode == A_KEY)
    {
        data->player_x -= step;
        printf("left\n");
    }
    else if (keycode == UP_ARROW || keycode == W_KEY)
    {
        data->player_y -= step;
        printf("up\n");
    }
    else if (keycode == RIGHT_ARROW || keycode == D_KEY)
    { 
        data->player_x += step;
        printf("right\n");
    }
    else if (keycode == DOWN_ARROW || keycode == S_KEY) 
    {
        data->player_y += step;
        printf("down\n");
    }
    else if (keycode == ESCAPE)
	{
        printf("exit\n");
		mlx_destroy_window(data->mlx, data->win);
		exit (0);
	}
    mlx_clear_window(data->mlx, data->win);
    draw_map(data);
    draw_player(data);

    return 0;
}