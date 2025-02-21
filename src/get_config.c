/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:05 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/18 18:08:01 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static unsigned int	rgb_to_hex(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static char *extract_texture_path(char *line, const char type)
{
	char *path;

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

int get_textures(char *line, const char type, t_data *data)
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
	else if (! data->west_texture && type == 'W' && path)
		data->west_texture = ft_strdup(path);
	else
		return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int	get_colors(char *line, const char type, t_data *data)
{
	char	**rgb_values;
	int		rgb[3];

	if (type == 'N' || type == 'W' || type == 'S' || type == 'E')
		return (EXIT_SUCCESS);
	line++;
	while (line && ft_isdigit(*line) == 0)
		line++;
	rgb_values = ft_split(line, ',');
	rgb[0] = ft_atoi(rgb_values[0]);
	rgb[1] = ft_atoi(rgb_values[1]);
	rgb[2] = ft_atoi(rgb_values[2]);
	if (type == 'F')
		data->floor_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	if (type == 'C')
		data->ceiling_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	ft_free_array(rgb_values);

	return (EXIT_SUCCESS);
}
inline static void free_lines(char *lines[6])
{
	int i;
	
	i = 0;
	while (lines[i] && i <= 5)
	{
		free(lines[i]);
		i++;	
	}
	
}

int	get_config(int fd, t_data *data)
{
	static char	keys[7] = {'N', 'S', 'E', 'W', 'F', 'C', 0};
	char		*lines[6];
	int			i;
	int			k;

	i = 0;
	lines[6] = NULL;
	while (i <= 5)
	{
		lines[i] = gnl_smart(fd);
			if (!lines[i])
				return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (lines[i] && i <= 5)
	{
		k = 0;
		while (keys[k] && lines[i][0] != keys[k])
			k++;
		if (get_textures(lines[i], keys[k], data) == EXIT_FAILURE || get_colors(lines[i], keys[k], data) == EXIT_FAILURE)
			return (free_lines(lines), EXIT_FAILURE);
		i++;
	}
	free_lines(lines);
	if (i < 5)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
