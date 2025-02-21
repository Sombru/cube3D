/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/21 17:21:03 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	action(int keycode, t_data *data)
{
	float step = 10;
	float angle_diff = 0.1;

	if (keycode == A_KEY)
	{
		data->player_x += data->player_d_y * step;
		data->player_y -= data->player_d_x * step;
	}
	else if (keycode == W_KEY)
	{
		data->player_x += data->player_d_x * step;
		data->player_y += data->player_d_y * step;
	}
	else if (keycode == D_KEY)
	{
		data->player_x -= data->player_d_y * step;
		data->player_y += data->player_d_x * step;
	}
	else if (keycode == S_KEY)
	{
		data->player_x -= data->player_d_x * step;
		data->player_y -= data->player_d_y * step;
	}
	else if (keycode == LEFT_ARROW)
	{
		data->player_a -= angle_diff;
		if (data->player_a < 0)
			data->player_a += 2 * PI;
		data->player_d_x = cos(data->player_a);
		data->player_d_y = sin(data->player_a);
	}
	else if (keycode == RIGHT_ARROW)
	{
		data->player_a += angle_diff;
		if (data->player_a > 2 * PI)
			data->player_a -= 2 * PI;
		data->player_d_x = cos(data->player_a);
		data->player_d_y = sin(data->player_a);
	}
	else if (keycode == ESCAPE)
	{
		printf("exit\n");
		mlx_destroy_image(data->mlx, data->frame_2d);
		mlx_destroy_image(data->mlx, data->frame_3d);
        mlx_destroy_image(data->mlx, data->textures[0].img);
        mlx_destroy_image(data->mlx, data->textures[1].img);
        mlx_destroy_image(data->mlx, data->textures[2].img);
        mlx_destroy_image(data->mlx, data->textures[3].img);
		mlx_destroy_window(data->mlx, data->win_2d);
		mlx_destroy_window(data->mlx, data->win_3d);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data->map);
		free(data);
		exit(0);
	}
	render_frame(data);
	return (0);
}