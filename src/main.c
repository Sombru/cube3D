/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/01/30 14:51:52 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	main(void)
{
	t_data			*data;
	t_player_pos	*player_pos;
	
    data = malloc(sizeof(t_data));
	player_pos = malloc(sizeof(t_player_pos));
	data->map = malloc((sizeof(int)) * 200);
	data->map_size = 100;
	data->map_x = 10;
	data->map_y = 10;
    int map[100] = {
        1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,1,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,0,1,
        1,0,0,0,0,0,0,1,0,1,
        1,1,1,1,1,1,1,1,1,1
    };
    int i = 0;
    while (i < 100)
    {
        data->map[i] = map[i];
        i++;
    }
	window_loop(data);
}
