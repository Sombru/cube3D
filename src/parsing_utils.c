/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:29:45 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/11 16:18:33 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// skips empty lines in a file
char	*skip_nl(int fd)
{
    char *nl;

    nl = get_next_line(fd);
    while (nl && nl[0] == '\n')
    {
        free(nl);
        nl = get_next_line(fd);
    }
    return (nl);
}

static char *extract_texture_path(char *line, const char *type)
{
	char *path;

	path = NULL;
    if (ft_strncmp(line, type, ft_strlen(type)) == 0)
    {
        path = ft_strchr(line, '/');
        if (path)
            return (path + 1);
    }
    return (NULL);
}

int get_textures(char **config, t_data *data)
{
	char	*path;
    int 	i;

	i = 0;
	while (i < 4)
	{
		if ((path = extract_texture_path(config[i], "NO")) != NULL)
			data->north_texture = path;
		else if ((path = extract_texture_path(config[i], "SO")) != NULL)
			data->south_texture = path;
		else if ((path = extract_texture_path(config[i], "WE")) != NULL)
			data->west_texture = path;
		else if ((path = extract_texture_path(config[i], "EA")) != NULL)
			data->east_texture = path;
		else
			return (EXIT_FAILURE);
		i++;
	}
    return (EXIT_SUCCESS);
}