/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/26 17:11:50 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void window_loop(t_data **data)
{
    *data = malloc(sizeof(t_data));
    (*data)->mlx = mlx_init();
    (*data)->win = mlx_new_window((*data)->mlx, 1440, 720, "Cube3D");
    (*data)->player_x = 200;
    (*data)->player_y = 200;
    mlx_loop_hook((*data)->mlx, action, data);
    mlx_loop((*data)->mlx);
}
