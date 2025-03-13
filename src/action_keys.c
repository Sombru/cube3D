/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:47 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/13 11:24:46 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	handle_key_a(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.d_y * STEP;
	new_y = data->player.y - data->player.d_x * STEP;
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_key_w(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + data->player.d_x * STEP;
	new_y = data->player.y + data->player.d_y * STEP;
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_key_d(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.d_y * STEP;
	new_y = data->player.y + data->player.d_x * STEP;
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_key_s(t_data *data)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x - data->player.d_x * STEP;
	new_y = data->player.y - data->player.d_y * STEP;
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void	handle_key_left(t_data *data)
{
	data->player.a -= ANGLE_DIFF;
	if (data->player.a < 0)
		data->player.a += 2 * PI;
	data->player.d_x = cos(data->player.a);
	data->player.d_y = sin(data->player.a);
}
