/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:11:07 by sombru            #+#    #+#             */
/*   Updated: 2025/03/13 10:11:37 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	is_map_closed(int fd, char **map, t_data *data)
{
	int	i;

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
static void	get_player_angle(char map_line, t_data *data)
{
	if (map_line == 'N')
		data->player.a = 3 * PI / 2;
	else if (map_line == 'S')
		data->player.a = PI / 2;
	else if (map_line == 'E')
		data->player.a = 0;
	else if (map_line == 'W')
		data->player.a = PI;
}

void	get_player_pos(int fd, char **map_parse, t_data *data)
{
	static int	i[3] = {0, 0, 0};

	while (map_parse[i[0]])
	{
		i[2] = 0;
		while (map_parse[i[0]][i[2]])
		{
			if (map_parse[i[0]][i[2]] == 'N' || map_parse[i[0]][i[2]] == 'S'
				|| map_parse[i[0]][i[2]] == 'E' || map_parse[i[0]][i[2]] == 'W')
			{
				if (data->player.x)
					safe_exit(fd, map_parse, data, "more than 1 player pos\n");
				data->player.x = i[2] * data->block_size + data->block_size / 2;
				data->player.y = i[0] * data->block_size + data->block_size / 2;
				get_player_angle(map_parse[i[0]][i[2]], data);
				data->map[i[1]++] = '0';
			}
			else
				data->map[i[1]++] = map_parse[i[0]][i[2]];
			i[2]++;
		}
		i[0]++;
	}
	data->map[i[1]] = '\0';
}
