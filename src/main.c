/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/03/11 06:52:45 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	exit_game(t_data *data)
{
	free(data->north_texture);
	free(data->west_texture);
	free(data->east_texture);
	free(data->south_texture);
	mlx_destroy_image(data->mlx, data->north.img);
	mlx_destroy_image(data->mlx, data->east.img);
	mlx_destroy_image(data->mlx, data->south.img);
	mlx_destroy_image(data->mlx, data->west.img);
	mlx_destroy_image(data->mlx, data->frame_2d);
	mlx_destroy_image(data->mlx, data->frame_3d);
	mlx_destroy_window(data->mlx, data->win_2d);
	mlx_destroy_window(data->mlx, data->win_3d);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->map);
	free(data->original_map);
	free(data);
	exit(0);
}

void	init_data(t_data *data)
{
	data->block_size = 50;
	data->player.a = 0;
	data->player.y = 0;
	data->player.x = 0;
	data->player.d_x = 0;
	data->player.d_y = 0;
	data->minimap_size = 720;
	data->screen_width = 1440;
	data->screen_height = 720;
	data->map = NULL;
	data->west_texture = NULL;
	data->south_texture = NULL;
	data->north_texture = NULL;
	data->east_texture = NULL;
	data->door_timer = 0;
	data->original_map = NULL;
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc == 1)
		return (write(STDERR_FILENO, "Specify map to read\n", 21));
	if (argc == 3)
		return (write(STDERR_FILENO, "Too many arguments\n", 20));
	if (ft_strcmp(ft_strchr(argv[1], '.'), ".cub") != 0)
		return(write(STDERR_FILENO, "Map file must end with \".cub\"\n", 31));
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(STDERR_FILENO, "Memory allocation failed\n", 25));
	init_data(data);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free(data);
		return (write(STDERR_FILENO, "MLX initialization failed\n", 26));
	}
	get_map(argv[argc - 1], data);
	data->player.d_x = cos(data->player.a);
	data->player.d_y = sin(data->player.a);
	window_loop(data);
	exit_game(data);
	return (0);
}
