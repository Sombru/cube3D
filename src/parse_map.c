/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/27 08:00:46 by nspalevi         ###   ########.fr       */
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

	res = malloc(sizeof(res) * (data->map_x + 1));
	i = 0;
	j = 0;
	while (map_line[i])
	{
		if (map_line[i] == ' ')
			res[j++] = '1';
		else if (map_line[i] == '\t')
			j = put_tab(res, j);
		else if (map_line[i] == '2')
			res[j++] = '2';
		else
			res[j++] = map_line[i];
		i++;
	}
	while (j < data->map_x)
		res[j++] = '1';
	res[j] = '\0';
	return (free(map_line), res);
}

static int	read_map_lines(int fd, char *map[], int *x, int *y)
{
	while (1)
	{
		map[*y] = gnl_smart(fd);
		if (!map[*y])
			break ;
		if (!is_valid_map_line(map[*y]))
		{
			while (*y >= 0)
			{
				free(map[*y]);
				(*y)--;
			}
			return (EXIT_FAILURE);
		}
		if ((int)ft_strlen(map[*y]) > *x)
			*x = ft_strlen(map[*y]);
		(*y)++;
	}
	return (EXIT_SUCCESS);
}

static char	**parse_map(int fd, t_data *data)
{
	char	*map[200];
	char	**parsed;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (read_map_lines(fd, map, &x, &y) == EXIT_FAILURE)
		return (NULL);
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
	data->east.img = mlx_xpm_file_to_image(data->mlx, data->east_texture,
			&data->east.width, &data->east.height);
	data->south.img = mlx_xpm_file_to_image(data->mlx, data->south_texture,
			&data->south.width, &data->south.height);
	data->west.img = mlx_xpm_file_to_image(data->mlx, data->west_texture,
			&data->west.width, &data->west.height);
	data->door.img = mlx_xpm_file_to_image(data->mlx, data->door_texture,
			&data->door.width, &data->door.height);
	if (!data->north.img || !data->east.img || !data->south.img
		|| !data->west.img || !data->door.img)
		return (EXIT_FAILURE);
	data->north.data = (int *)mlx_get_data_addr(data->north.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->east.data = (int *)mlx_get_data_addr(data->east.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->south.data = (int *)mlx_get_data_addr(data->south.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->west.data = (int *)mlx_get_data_addr(data->west.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	data->door.data = (int *)mlx_get_data_addr(data->door.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	return (EXIT_SUCCESS);
}

void	get_map(char *map_path, t_data *data)
{
	char		**map_parse;
	int			fd;
	static int	i = 0;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		safe_exit(fd, NULL, data, "Error opening map file\n");
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
	while (i < data->map_x * data->map_y + 1)
	{
		data->original_map[i] = data->map[i];
		i++;
	}
	is_map_closed(fd, map_parse, data);
	ft_free_array(map_parse);
}
