/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/24 13:18:40 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static int	check_collision(t_data *data, float new_x, float new_y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)(new_x / data->block_size);
	map_y = (int)(new_y / data->block_size);
	if (map_x < 0 || map_x >= data->map_x || map_y < 0 || map_y >= data->map_y)
		return (1);
	cell = data->map[map_y * data->map_x + map_x];
	return (cell == '1' || cell == '2');
}

static void	handle_door(t_data *data)
{
	float	check_distance;
	float	check_x;
	float	check_y;
	int		map_x;
	int		map_y;
	int		map_index;

	check_distance = 30.0f;
	check_x = data->player_x + data->player_d_x * check_distance;
	check_y = data->player_y + data->player_d_y * check_distance;
	map_x = (int)(check_x / data->block_size);
	map_y = (int)(check_y / data->block_size);
	if (map_x >= 0 && map_x < data->map_x && map_y >= 0 && map_y < data->map_y)
	{
		map_index = map_y * data->map_x + map_x;
		if (data->map[map_index] == '2')
		{
			// Open door: mark it open ('0') and start the 5‑second timer (300 frames)
			data->map[map_index] = '0';
			data->door_timer = 300;
		}
	}
}

int	action(int keycode, t_data *data)
{
	float	step;
	float	angle_diff;

	step = 10;
	angle_diff = 0.1;
	float new_x, new_y;
	if (keycode == SPACE)
	{
		handle_door(data);
	}
	else if (keycode == A_KEY)
	{
		new_x = data->player_x + data->player_d_y * step;
		new_y = data->player_y - data->player_d_x * step;
		if (!check_collision(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	else if (keycode == W_KEY)
	{
		new_x = data->player_x + data->player_d_x * step;
		new_y = data->player_y + data->player_d_y * step;
		if (!check_collision(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	else if (keycode == D_KEY)
	{
		new_x = data->player_x - data->player_d_y * step;
		new_y = data->player_y + data->player_d_x * step;
		if (!check_collision(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
	}
	else if (keycode == S_KEY)
	{
		new_x = data->player_x - data->player_d_x * step;
		new_y = data->player_y - data->player_d_y * step;
		if (!check_collision(data, new_x, new_y))
		{
			data->player_x = new_x;
			data->player_y = new_y;
		}
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
