/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:05 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/14 16:40:14 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static unsigned int	rgb_to_hex(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static char *extract_texture_path(char *line, const char *type)
{
	char *path;

	path = NULL;
    if (ft_strncmp(line, type, ft_strlen(type)) == 0)
    {
        path = ft_strdup(ft_strchr(line, '/'));
		free(line);
        if (path)
		{
			ft_bzero(path, 1);
            return (path);
		}
    }
    return (NULL);
}

int get_textures(int fd, t_data *data)
{
	char	*path;
	char 	*line;
    int 	i;

	i = 0;
	while (i < 4)
	{
		line = gnl_smart(fd);
		if ((path = extract_texture_path(line, "NO")) != NULL)
			data->north_texture = path;
		else if ((path = extract_texture_path(line, "SO")) != NULL)
			data->south_texture = path;
		else if ((path = extract_texture_path(line, "WE")) != NULL)
			data->west_texture = path;
		else if ((path = extract_texture_path(line, "EA")) != NULL)
			data->east_texture = path;
		else
			return (free(line), EXIT_FAILURE);
		i++;
	}
    return (EXIT_SUCCESS);
}

int	get_colors(int fd, t_data *data)
{
	char	**rgb_values[2];
	char	*lines[2];
	int		rgb[6];
	int 	i;

	lines[0] = gnl_smart(fd);
	lines[1] = gnl_smart(fd);
	if (!lines[0] || !lines[1])
		return (EXIT_FAILURE);
	if (lines[0][0] == lines[1][0] || (lines[0][0] != 'F' && lines[0][0] != 'C') || (lines[1][0] != 'F' && lines[1][0] != 'C'))
		return (free(lines[0]), free(lines[1]), EXIT_FAILURE);
	rgb_values[0] = ft_split(lines[0], ',');
	rgb_values[1] = ft_split(lines[1], ',');
	free(lines[0]);
	free(lines[1]);
	if (ft_count_args(rgb_values[0]) != 3 || ft_count_args(rgb_values[1]) != 3)
		return (ft_free_array(rgb_values[0]), ft_free_array(rgb_values[0]), EXIT_FAILURE);
	i = 0;
	while (i <= 2)
	{
		rgb[i] = ft_atoi(rgb_values[0][i]);
		rgb[i + 3] = ft_atoi(rgb_values[1][i]);
		i++;
	}
	data->floor_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	data->ceiling_color = rgb_to_hex(rgb[3], rgb[4], rgb[5]);
	ft_free_array(rgb_values[1]);
	ft_free_array(rgb_values[0]);
	return (EXIT_SUCCESS);
}

    // if (config[4][0] == 'F' || config[5][0] == 'C')
    // {
    //     i = 0;
    //     rgb_values = ft_split(config[4] + 2, ',');
    //     while (i <= 2)
    //     {
    //         rgb[i] = ft_atoi(rgb_values[i]);
    //         i++;
    //     }
    //     ft_free_array(rgb_values);
    //     if (config[4][0] == 'F')
    //         data->floor_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
    //     rgb_values = ft_split(config[5] + 2, ',');
    //     while (i <= 5)
    //     {
    //         rgb[i] = ft_atoi(rgb_values[i - 3]);
    //         i++;
    //     }
    //     ft_free_array(rgb_values);
    //     if (config[5][0] == 'C')
    //         data->ceiling_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
    // }