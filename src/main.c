/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/03/24 09:13:17 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	exit_game(t_data *data)
{
	free(data->north_texture);
	free(data->west_texture);
	free(data->east_texture);
	free(data->south_texture);
	free(data->door_texture);
	mlx_destroy_image(data->mlx, data->north.img);
	mlx_destroy_image(data->mlx, data->east.img);
	mlx_destroy_image(data->mlx, data->south.img);
	mlx_destroy_image(data->mlx, data->west.img);
	mlx_destroy_image(data->mlx, data->door.img);
	mlx_destroy_image(data->mlx, data->frame_2d);
	mlx_destroy_image(data->mlx, data->frame_3d);
	mlx_destroy_window(data->mlx, data->win_3d);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->map);
	free(data->original_map);
	free(data);
	exit(0);
}

static void	init_player_and_keys(t_data *data)
{
	data->player.a = 0;
	data->player.y = 0;
	data->player.x = 0;
	data->player.d_x = 0;
	data->player.d_y = 0;
	data->player.size = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.w = 0;
	data->keys.m = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.space = 0;
}

static void	init_textures(t_data *data)
{
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->east_texture = NULL;
	data->west_texture = NULL;
	data->door_texture = NULL;
	ft_bzero(&data->north, sizeof(t_texture));
	ft_bzero(&data->south, sizeof(t_texture));
	ft_bzero(&data->east, sizeof(t_texture));
	ft_bzero(&data->west, sizeof(t_texture));
	ft_bzero(&data->door, sizeof(t_texture));
}

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->mlx = mlx_init();
	data->block_size = 50;
	data->minimap_size = MINIMAP_SIZE;
	data->screen_width = SCREEN_WIDTH;
	data->screen_height = SCREEN_HEIGHT;
	data->door_timer = 0;
	data->off_x = 0;
	data->off_y = 0;
	data->start_angle = 0;
	data->angle_step = 0;
	data->scaled_size = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->map_size = 0;
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->map = NULL;
	data->original_map = NULL;
	init_player_and_keys(data);
	init_textures(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 1)
		return (write(STDERR_FILENO, "Specify map to read\n", 21));
	if (argc == 3)
		return (write(STDERR_FILENO, "Too many arguments\n", 20));
	if (ft_strchr(argv[1], '.') == NULL)
		return (write(STDERR_FILENO, "Map file must end with \".cub\"\n", 31));
	if (ft_strcmp(ft_strchr(argv[1], '.'), ".cub") != 0)
		return (write(STDERR_FILENO, "Map file must end with \".cub\"\n", 31));
	data = malloc(sizeof(t_data));
	if (!data)
		return (write(STDERR_FILENO, "Memory allocation failed\n", 25));
	init_data(data);
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
