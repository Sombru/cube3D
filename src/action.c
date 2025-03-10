/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:03:27 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/10 07:17:33 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static int	check_collision(t_data *data, float new_x, float new_y)
{
	int		map_x;
	int		map_y;
	char	cell;

	// return(0);
	map_x = (int)(new_x / data->block_size);
	map_y = (int)(new_y / data->block_size);
	if (map_x < 0 || map_x >= data->map_x || map_y < 0 || map_y >= data->map_y)
		return (1);
	cell = data->map[map_y * data->map_x + map_x];
	return (cell == '1' || cell == '2');
}

static void	handle_door(t_data *data)
{
	float	check_x;
	float	check_y;
	int		map_x;
	int		map_y;
	int		map_index;

	check_x = data->player.x + data->player.d_x * DOOR_RANGE;
	check_y = data->player.y + data->player.d_y * DOOR_RANGE;
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

int	key_press_handler(int keycode, t_data *data)
{
    if (keycode == SPACE)
        data->keys.space = 1;
    else if (keycode == A_KEY)
        data->keys.a = 1;
    else if (keycode == W_KEY)
        data->keys.w = 1;
    else if (keycode == D_KEY)
        data->keys.d = 1;
    else if (keycode == S_KEY)
        data->keys.s = 1;
    else if (keycode == LEFT_ARROW)
        data->keys.left = 1;
    else if (keycode == RIGHT_ARROW)
        data->keys.right = 1;
    else if (keycode == ESCAPE)
    {
        printf("exit\n");
        exit_game(data);
    }
    return (0);
}

int	key_release_handler(int keycode, t_data *data)
{
    if (keycode == SPACE)
        data->keys.space = 0;
    else if (keycode == A_KEY)
        data->keys.a = 0;
    else if (keycode == W_KEY)
        data->keys.w = 0;
    else if (keycode == D_KEY)
        data->keys.d = 0;
    else if (keycode == S_KEY)
        data->keys.s = 0;
    else if (keycode == LEFT_ARROW)
        data->keys.left = 0;
    else if (keycode == RIGHT_ARROW)
        data->keys.right = 0;
    return (0);
}

int	action(t_data *data)
{
    float	new_x, new_y;

    if (data->keys.space)
        handle_door(data);
    if (data->keys.a)
    {
        new_x = data->player.x + data->player.d_y * STEP;
        new_y = data->player.y - data->player.d_x * STEP;
        if (!check_collision(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (data->keys.w)
    {
        new_x = data->player.x + data->player.d_x * STEP;
        new_y = data->player.y + data->player.d_y * STEP;
        if (!check_collision(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (data->keys.d)
    {
        new_x = data->player.x - data->player.d_y * STEP;
        new_y = data->player.y + data->player.d_x * STEP;
        if (!check_collision(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (data->keys.s)
    {
        new_x = data->player.x - data->player.d_x * STEP;
        new_y = data->player.y - data->player.d_y * STEP;
        if (!check_collision(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (data->keys.left)
    {
        data->player.a -= ANGLE_DIFF;
        if (data->player.a < 0)
            data->player.a += 2 * PI;
        data->player.d_x = cos(data->player.a);
        data->player.d_y = sin(data->player.a);
    }
    if (data->keys.right)
    {
        data->player.a += ANGLE_DIFF;
        if (data->player.a > 2 * PI)
            data->player.a -= 2 * PI;
        data->player.d_x = cos(data->player.a);
        data->player.d_y = sin(data->player.a);
    }
    printf("Player position: %f %f\n", data->player.x, data->player.y);
    printf("Player direction: %f %f\n", data->player.d_x, data->player.d_y);
    return (0);
}
