/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/02/17 13:24:28 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	main(void)
{
	t_data			*data;
	
	data = malloc(sizeof(t_data));
	data->map_size = 100;
	data->block_size = 73;
	data->map = malloc((sizeof(data->map)) * data->map_size);
	data->map_x = 10;
	data->map_y = 10;
	data->player_a = 0;
	data->player_d_x = cos(data->player_a);
	data->player_d_y = sin(data->player_a);
	data->mlx = mlx_init();
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
	load_textures(data);
	window_loop(data);
}
