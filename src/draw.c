/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/01/26 17:03:43 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int draw_player(t_data *data)
{
    int x, y;
    int size = 10; // Size of the square

    for (y = data->player_y; y < data->player_y + size; y++)
    {
        for (x = data->player_x; x < data->player_x + size; x++)
        {
            mlx_pixel_put(data->mlx, data->win, x, y, GREEN);
        }
    }
    return 0;
}
