/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:10:33 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/17 09:50:10 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

t_coord	line_coords(int x0, int y0, int x1, int y1)
{
	t_coord	coord;

	coord.x0 = x0;
	coord.x1 = x1;
	coord.y0 = y0;
	coord.y1 = y1;
	return (coord);
}

int	put_tab(char *res, int j)
{
	res[j++] = '1';
	res[j++] = '1';
	res[j++] = '1';
	res[j++] = '1';
	return (j);
}

// did not fit into other key handler functions 
void	handle_key_right(t_data *data)
{
	data->player.a += ANGLE_DIFF;
	if (data->player.a > 2 * PI)
		data->player.a -= 2 * PI;
	data->player.d_x = cos(data->player.a);
	data->player.d_y = sin(data->player.a);
}

void	debug_map(char **map, t_data *data)
{
	int	i;

	i = 0;
	printf("data->north_textures: %s\n", data->north_texture);
	printf("data->south_textures: %s\n", data->south_texture);
	printf("data->west_textures: %s\n", data->west_texture);
	printf("data->east_textures: %s\n", data->east_texture);
	printf("data->door_textures: %s\n", data->door_texture);
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
