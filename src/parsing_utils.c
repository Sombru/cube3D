/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:29:45 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/27 08:35:00 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	free_config(t_data *data)
{
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->door_texture)
		free(data->door_texture);
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->door.img)
		mlx_destroy_image(data->mlx, data->door.img);
}

void	free_gnl_buffer(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	is_valid_map_key(char c)
{
	static const char	valid_keys[] = "012 \tNSEW";
	int					i;

	i = 0;
	while (valid_keys[i])
	{
		if (c == valid_keys[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_map_line(char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i])
	{
		if (!is_valid_map_key(map_line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	safe_exit(int fd, char **map, t_data *data, const char *message)
{
	write(2, message, ft_strlen(message));
	if (read(fd, NULL, 0) != -1)
		free_gnl_buffer(fd);
	free_config(data);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (map)
		ft_free_array(map);
	if (data->map)
	{
		free(data->map);
		free(data->original_map);
	}
	free(data);
	exit(69);
}
