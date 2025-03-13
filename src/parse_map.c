/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/13 09:51:42 by pkostura         ###   ########.fr       */
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
//  normette

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
			res[j++] = '1';
		else if (map_line[i] == '\t')
		{
			res[j++] = '1';
			res[j++] = '1';
			res[j++] = '1';
			res[j++] = '1';
		}
		else if (map_line[i] == '2') // door handling
			res[j++] = '2';
		else
			res[j++] = map_line[i];
		i++;
	}
	while (j < data->map_x)
		res[j++] = '1';
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

static int	load_textures(t_data *data)
{
	data->north.img = mlx_xpm_file_to_image(data->mlx, data->north_texture,
			&data->north.width, &data->north.height);
	if (!data->north.img)
		return (EXIT_FAILURE);
	data->north.data = (int *)mlx_get_data_addr(data->north.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->east.img = mlx_xpm_file_to_image(data->mlx, data->east_texture,
			&data->east.width, &data->east.height);
	if (!data->east.img)
		return (EXIT_FAILURE);
	data->east.data = (int *)mlx_get_data_addr(data->east.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->south.img = mlx_xpm_file_to_image(data->mlx, data->south_texture,
			&data->south.width, &data->south.height);
	if (!data->south.img)
		return (EXIT_FAILURE);
	data->south.data = (int *)mlx_get_data_addr(data->south.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->west.img = mlx_xpm_file_to_image(data->mlx, data->west_texture,
			&data->west.width, &data->west.height);
	if (!data->west.img)
		return (EXIT_FAILURE);
	data->west.data = (int *)mlx_get_data_addr(data->west.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->door.img = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm",
			&data->door.width, &data->door.height);
	if (!data->door.img)
		return (EXIT_FAILURE);
	data->door.data = (int *)mlx_get_data_addr(data->door.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return (EXIT_SUCCESS);
}

void	get_map(char *map_path, t_data *data)
{
	char			**map_parse;
	int				fd;
	static int		i = 0;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		free(data);
		exit(write(2, "Error opening map file\n", 23));
	}
	if (get_config(fd, data) == EXIT_FAILURE)
		safe_exit(fd, NULL, data, "Error in map config\n");
	if (load_textures(data) == EXIT_FAILURE)
		safe_exit(fd, NULL, data, "Error loading textures\n");
	map_parse = parse_map(fd, data);
	if (!map_parse)
		safe_exit(fd, NULL, data, "Error parsing map\n");
	data->map = malloc(data->map_x * data->map_y + 1);
	data->original_map = malloc(data->map_x * data->map_y + 1);
	get_player_pos(fd, map_parse, data);
	while (i++ < data->map_x * data->map_y + 1)
		data->original_map[i] = data->map[i];
	is_map_closed(fd, map_parse, data);
	debug_map(map_parse, data);
	ft_free_array(map_parse);
}
