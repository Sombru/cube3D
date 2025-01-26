/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/26 16:18:20 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int close_win(int keycode, t_data *data)
{
	(void)keycode;
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}
void window_loop(t_data **data)
{
    *data = malloc(sizeof(t_data));
    (*data)->mlx = mlx_init();
    (*data)->win = mlx_new_window((*data)->mlx, 1440, 720, "Cube3D");
    (*data)->player_x = 200;
    (*data)->player_y = 200;
    mlx_key_hook((*data)->win, move_player, *data); // Hook move_player to key press events
    mlx_hook((*data)->win, 17, 0, close_win, *data); // Hook close_win to window close event
    mlx_loop_hook((*data)->mlx, draw_player, *data); // Hook draw_player to the loop
    mlx_loop((*data)->mlx);
}
