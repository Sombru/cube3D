/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/21 18:31:27 by nspalevi         ###   ########.fr       */
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
		exit_game(data);
	}
	render_frame(data);
	return (0);
}