/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:10:33 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/10 07:01:54 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	debug_map(char	**map, t_data *data)
{
	int i;

	i = 0;
	printf("data->north_textures: %s\n", data->north_texture);
    printf("data->south_textures: %s\n", data->south_texture);
    printf("data->west_textures: %s\n", data->west_texture);
    printf("data->east_textures: %s\n", data->east_texture);
    printf("floor: %X\n", data->floor_color);
    printf("ceiling: %X\n", data->ceiling_color);
	printf("data->map_y: %d\n", data->map_y);
    printf("data->map_x: %d\n", data->map_x);
	printf("player y: %f\n", data->player.y);
	printf("playe. x: %f\n", data->player.x);
	while (map[i])
	{
		printf("map[%d]: %s\n", i, map[i]);
		i++;
	}
}
