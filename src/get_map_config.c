/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:11:07 by sombru            #+#    #+#             */
/*   Updated: 2025/02/21 19:04:30 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static void get_player_angle(char map_line, t_data *data)
{
	if (map_line == 'N')
		data->player_a = 3 * PI / 2;
	else if (map_line == 'S')
		data->player_a = PI / 2;
	else if (map_line == 'E')
		data->player_a = 0;
	else if (map_line == 'W')
		data->player_a = PI;
}

void	is_map_closed(int fd, char **map, t_data *data)
{
    int i;

	i = 0;
	while (i < data->map_x)
	{
		if (map[0][i] != '1' || map[data->map_y - 1][i] != '1')
			safe_exit(fd, map, data, "map not closed by walls\n");
		i++;
	}
	i = 0;
	while (i < data->map_y)
	{
		if (map[i][0] != '1' || map[i][data->map_x - 1] != '1')
			safe_exit(fd, map, data, "map not closed by walls\n");
		i++;
	}
}

void	get_player_pos(int fd, char **map_parse, t_data *data)
{
	static int	i = 0;
	static int	j = 0;
	static int	k = 0;

	while (map_parse[i])
	{
		k = 0;
		while (map_parse[i][k])
		{
			if (map_parse[i][k] == 'N' || map_parse[i][k] == 'S'
				|| map_parse[i][k] == 'E' || map_parse[i][k] == 'W')
			{
				if (data->player_x)
					safe_exit(fd, map_parse, data, "more than 1 player pos\n");
				data->player_x = k * data->block_size + data->block_size / 2;
				data->player_y = i * data->block_size + data->block_size / 2;
				get_player_angle(map_parse[i][k], data);
				data->map[j++] = '0';
			}
			else
				data->map[j++] = map_parse[i][k];
			k++;
		}
		i++;
	}
	data->map[j] = '\0';
}
