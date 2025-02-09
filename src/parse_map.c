/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/09 22:18:53 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// map will be first parsed into array of strings
// the amount of strings is map_y
// the longest string is map_x
// spaces will be converted into walls
// tabs into 4 walls
// player_a will depend on weather is N, W, E ,S is player
// char **args

static unsigned int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// static void get_texture(char **config, t_data *data, int fd)
// {
// 	int i = 0;
	
// 	while (i <= 3)
// 	{
// 		config[i] = get_next_line(fd);
// 		config[i] = ft_rmlast_char(config[i], '\n');
// 		config[i] = ft_strchr(config[i], '/');
// 		if(!config[i])
// 			exit(write(2, "not valid textures\n", 20));
// 		config[i]++;
// 		data->textures[i] = config[i];
// 		printf("data->textures: %s\n", data->textures[i]);
// 		i++;
// 	}	
// }

static char **get_config(int fd, t_data *data)
{
	char **config;
	int i;

	config = malloc(sizeof(config) * (7));
	i = 0;
	while (i <= 6)
	{
		config[i] = get_next_line(fd);
		if (!config[i])
			exit(write(2, "not valid map format\n", 22));
		config[i] = ft_rmlast_char(config[i], '\n');
		i++;
	}
	i = 0;
	while (i <= 3)
	{
		config[i] = ft_strchr(config[i], '/');
		if(!config[i])
			exit(write(2, "not valid textures\n", 20));
		config[i]++;
		data->textures[i] = config[i];
		i++;
	}
	return(config);
}

char	*get_map(char *map_path, t_data *data)
{
	int		fd;
	char	**config;
	char	**rgb_values;
	int		rgb[6];
	int		i;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit(write(2, "could not open the file\n", 25));
	config = get_config(fd, data);
	if (config[5][0] == 'F' || config[6][0] == 'C')
	{
		i = 0;
		rgb_values = ft_split(config[5] + 2, ',');
		while (i <= 2)
		{
			rgb[i] = ft_atoi(rgb_values[i]);
			i++;
		}
		ft_free_array(rgb_values);
		if (config[5][0] == 'F')
			data->floor_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
		rgb_values = ft_split(config[6] + 2, ',');
		while (i <= 5)
		{
			rgb[i] = ft_atoi(rgb_values[i - 3]);
			i++;
		}
		ft_free_array(rgb_values);
		if (config[6][0] == 'C')
			data->ceiling_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	}
	printf("data->textures: %s\n", data->textures[0]);
	printf("data->textures: %s\n", data->textures[1]);
	printf("data->textures: %s\n", data->textures[2]);
	printf("data->textures: %s\n", data->textures[3]);

	printf("floor: %X\n", data->floor_color);
	printf("ceiling: %X\n", data->ceiling_color);
	close(fd);
	return ("tst");
}
