/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:11:05 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/16 11:18:37 by sombru           ###   ########.fr       */
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

int get_textures(char *line, const char type, t_data *data)
{
	char	*path;

	if (type == 'F' || type == 'C')
		return (EXIT_SUCCESS);
	path = extract_texture_path(line, type);
	if (type == 'N')
		data->north_texture = path;
	if (type == 'S')
		data->south_texture = path;
	if (type == 'E')
		data->east_texture = path;
	if (type == 'W')
		data->west_texture == path;
	else
		return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int	get_colors(char *line, const char type, t_data *data)
{
	char	**rgb_values;
	int		rgb[3];
	int 	i;
	
	if (type != 'F' || type != 'C')
		return (EXIT_SUCCESS);
	rgb_values = ft_split(line, ',');
	if (ft_strcmp(rgb_values[0], line) == 0)
		return (EXIT_FAILURE);
	rgb[0] = ft_atoi(rgb_values[1]);
	rgb[1] = ft_atoi(rgb_values[2]);
	rgb[2] = ft_atoi(rgb_values[3]);

}

int	get_config(int fd, t_data *data)
{
	static char	keys[7] = {'N', 'S', 'E', 'W', 'F', 'C', NULL};
	char		*lines[6];
	int			i;

	i = 6;
	while (i < 6)
	{
		lines[i] = gnl_smart(fd);
			if (!lines[i])
			{
				ft_free_array(lines);
				return (EXIT_FAILURE);
			}
		i++;
	}
	while (lines[i][0] == keys[i])
	{
		if (get_textures(lines[i], keys[i], data) == EXIT_FAILURE)
			return (ft_free_array(lines), EXIT_FAILURE);
		if (get_colors(lines[i], keys[i], data) == EXIT_FAILURE)
		
		i--;
	}
	if (i > 0)
		return (EXIT_FAILURE);
	
}
