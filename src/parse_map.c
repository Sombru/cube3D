/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/20 20:19:39 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// +map will be first parsed into array of strings
// +the amount of strings is map_y
// +the longest string is map_x
// +spaces will be converted into walls
// +tabs into 4 walls
// +player_a will depend on weather is N, W, E ,S is player
// +memory leaks
// +check validity of config
// +check valid map lines
// +check valid map borders
// +check exec player pos
// +-normette

static char	*get_map_line(char *map_line, t_data *data)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (data->map_x + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (map_line[i])
	{
		if (map_line[i] == ' ')
		{
			res[j++] = '1';
		}
		else if (map_line[i] == '\t')
		{
			res[j++] = '1';
			res[j++] = '1';
			res[j++] = '1';
			res[j++] = '1';
		}
		else
			res[j++] = map_line[i];
		i++;
	}
	while (j < data->map_x)
	{
		res[j++] = '1';
	}
	res[j] = '\0';
	free(map_line);
	return (res);
}

static char	**parse_map(int fd, t_data *data)
{
	char	*map[200];
	char	**parsed;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (1)
	{
		map[y] = gnl_smart(fd);
		if (!map[y])
			break ;
		if (!is_valid_map_line(map[y]))
		{
			while (y >= 0)
			{
				free(map[y]);
				y--;
			}
			return (NULL);
		}
		if ((int)ft_strlen(map[y]) > x)
			x = ft_strlen(map[y]);
		y++;
	}
	data->map_y = y;
	data->map_x = x;
	parsed = malloc(sizeof(parsed) * (data->map_y + 1));
	if (!parsed)
		return (NULL);
	y = 0;
	while (y < data->map_y)
	{
		parsed[y] = get_map_line(map[y], data);
		y++;
	}
	parsed[y] = NULL;
	return (parsed);
}

void	get_map(char *map_path, t_data *data)
{
	char	**map_parse;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		exit(write(2, "could not open the file\n", 25));
	}
	if (get_config(fd, data) == EXIT_FAILURE)
		safe_exit(fd, NULL, data, "bad config\n");
	map_parse = parse_map(fd, data);
	if (!map_parse)
		safe_exit(fd, NULL, data, "invalid map symbol\n");
	data->map = malloc(data->map_x * data->map_y + 1);
	get_player_pos(fd, map_parse, data);
	if (!data->player_x)
		safe_exit(fd, NULL, data, "missing player position\n");
	is_map_closed(fd, map_parse, data);
	debug_map(map_parse, data);
	ft_free_array(map_parse);
	free_gnl_buffer(fd);
}
