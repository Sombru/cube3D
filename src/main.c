/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/02/21 19:31:43 by nspalevi         ###   ########.fr       */
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
	free(data);
	exit(0);
}

void	init_data(t_data *data)
{
	data->block_size = 50;
	data->player_a = 0;
	data->player_y = 0;
	data->player_x = 0;
	data->player_d_x = 0;
	data->player_d_y = 0;
	data->minimap_size = 720;
	data->screen_width = 1440;
	data->screen_height = 720;
	data->map = NULL;
	data->west_texture = NULL;
	data->south_texture = NULL;
	data->north_texture = NULL;
	data->east_texture = NULL;
}

int	main(int argc, char **argv)
{
	t_data			*data;
	
	if (argc == 1)
		return(write(STDERR_FILENO, "Specify map to read\n", 21));
	if (argc == 3)
		return(write(STDERR_FILENO, "Too many arguments\n", 20));
	data = malloc(sizeof(t_data));
	init_data(data);
	data->mlx = mlx_init();
	get_map(argv[argc - 1], data);
	printf("playery y: %f\n", data->player_y);
	printf("playery x: %f\n", data->player_x);
	data->map_size = data->map_y * data->map_x;
	load_textures(data);
	window_loop(data);
	
}
