/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/05 18:54:30 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	action(int keycode, t_data *data)
{
	float step = 10; // Step size for movement
	float angle_diff = 0.1;

	if (keycode == A_KEY)
    {
        // Strafe left
        data->player_x += data->player_d_y * step;
        data->player_y -= data->player_d_x * step;
    }
    else if (keycode == W_KEY)
    {
        // Move forward
        data->player_x += data->player_d_x * step;
        data->player_y += data->player_d_y * step;
    }
    else if (keycode == D_KEY)
    {
        // Strafe right
        data->player_x -= data->player_d_y * step;
        data->player_y += data->player_d_x * step;
    }
    else if (keycode == S_KEY)
    {
        // Move backward
        data->player_x -= data->player_d_x * step;
        data->player_y -= data->player_d_y * step;
    }
    else if (keycode == LEFT_ARROW)
    {
        // Rotate left
        data->player_a -= angle_diff;
        if (data->player_a < 0)
            data->player_a += 2 * PI;
        data->player_d_x = cos(data->player_a);
        data->player_d_y = sin(data->player_a);
    }
    else if (keycode == RIGHT_ARROW)
    {
        // Rotate right
        data->player_a += angle_diff;
        if (data->player_a > 2 * PI)
            data->player_a -= 2 * PI;
        data->player_d_x = cos(data->player_a);
        data->player_d_y = sin(data->player_a);
    }
	else if (keycode == ESCAPE)
	{
		printf("exit\n");
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	mlx_clear_window(data->mlx, data->win);
	draw_map(data);
	draw_player(data);
	draw_direction(data);
	draw_rays(data);
	return (0);
}