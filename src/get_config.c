/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:05 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/17 10:10:56 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

inline static void	free_lines(char *lines[7])
{
	int	i;

	i = 0;
	while (lines[i] && i <= 6)
	{
		free(lines[i]);
		i++;
	}
}

static char	*extract_texture_path(char *line, const char type)
{
	char	*path;

	path = NULL;
	if (line[0] == type)
	{
		path = ft_strchr(line, '/');
		if (path)
		{
			path++;
			return (path);
		}
	}
	return (NULL);
}

int	get_textures(char *line, const char type, t_data *data)
{
	char	*path;

	if (type == 'F' || type == 'C')
		return (EXIT_SUCCESS);
	path = extract_texture_path(line, type);
	if (!data->north_texture && type == 'N' && path)
		data->north_texture = ft_strdup(path);
	else if (!data->south_texture && type == 'S' && path)
		data->south_texture = ft_strdup(path);
	else if (!data->east_texture && type == 'E' && path)
		data->east_texture = ft_strdup(path);
	else if (!data->west_texture && type == 'W' && path)
		data->west_texture = ft_strdup(path);
	else if (!data->door_texture && type == 'D' && path)
		data->door_texture = ft_strdup(path);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_colors(char *line, const char type, t_data *data)
{
	char	**rgb_values;
	int		rgb[3];

	if (type == 'N' || type == 'W' || type == 'S' || type == 'E' || type == 'D')
		return (EXIT_SUCCESS);
	line++;
	while (line && ft_isdigit(*line) == 0)
		line++;
	rgb_values = ft_split(line, ',');
	rgb[0] = ft_atoi(rgb_values[0]);
	rgb[1] = ft_atoi(rgb_values[1]);
	rgb[2] = ft_atoi(rgb_values[2]);
	if (type == 'F')
		data->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (type == 'C')
		data->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	ft_free_array(rgb_values);
	return (EXIT_SUCCESS);
}

int	get_config(int fd, t_data *data)
{
	static char	keys[8] = {'N', 'S', 'E', 'W', 'F', 'C', 'D', 0};
	static char	*lines[7] = {NULL};
	static int	i[2] = {0, 0};

	while (i[0] <= 6)
	{
		lines[i[0]] = gnl_smart(fd);
		if (!lines[i[0]])
			return (EXIT_FAILURE);
		i[0]++;
	}
	i[0] = 0;
	while (lines[i[0]] && i[0] <= 6)
	{
		i[1] = 0;
		while (keys[i[1]] && lines[i[0]][0] != keys[i[1]])
			i[1]++;
		if (get_textures(lines[i[0]], keys[i[1]], data) == 1
			|| get_colors(lines[i[0]], keys[i[1]], data) == 1)
			return (free_lines(lines), EXIT_FAILURE);
		i[0]++;
	}
	if (i[0] < 6)
		return (free_lines(lines), EXIT_FAILURE);
	return (free_lines(lines), EXIT_SUCCESS);
}
