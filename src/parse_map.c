/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/17 18:24:46 by pkostura         ###   ########.fr       */
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
// check valid map borders
// check exec player pos
// normette

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

char	*get_map(char *map_path, t_data *data)
{
	int		fd;
	char	**map_parse;
	int		i;
	char	*line;
	int		j;
	int		k;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		exit(write(2, "could not open the file\n", 25));
	}
	if (get_config(fd, data) == EXIT_FAILURE)
	{
		free_config(data);
		free_gnl_buffer(fd);
		exit(write(2, "bad config\n", 12));
	}
	map_parse = parse_map(fd, data);
	if (!map_parse)
	{
		free_config(data);
		free_gnl_buffer(fd);
		exit((write(2, "Invalid map line\n", 18)));
	}
	line = gnl_smart(fd);
	data->map = malloc(data->map_x * data->map_y + 1);
	if (!data->map)
		exit(write(2, "Memory allocation failed\n", 26));
	i = 0;
	j = 0;
	while (map_parse[i])
	{
		k = 0;
		while (map_parse[i][k])
		{
			if (map_parse[i][k] == 'N' || map_parse[i][k] == 'S'
				|| map_parse[i][k] == 'E' || map_parse[i][k] == 'W')
			{
				data->player_x = k * data->block_size + data->block_size / 2;
				data->player_y = i * data->block_size + data->block_size / 2;
				if (map_parse[i][k] == 'N')
					data->player_a = 3 * PI / 2;
				else if (map_parse[i][k] == 'S')
					data->player_a = PI / 2;
				else if (map_parse[i][k] == 'E')
					data->player_a = 0;
				else if (map_parse[i][k] == 'W')
					data->player_a = PI;
				data->player_d_x = cos(data->player_a);
				data->player_d_y = sin(data->player_a);
				data->map[j++] = '0'; // Replace player start pos
			}
			else
			{
				data->map[j++] = map_parse[i][k];
			}
			k++;
		}
		i++;
	}
	data->map[j] = '\0';
	debug_map(map_parse, data);
	ft_free_array(map_parse);
	free_gnl_buffer(fd);
	return ("tst");
}
