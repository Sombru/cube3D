/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/02/21 17:51:58 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"
// #include "action.c"
// #include "debug.c"
// #include "draw.c"
// #include "get_config.c"
// #include "parse_map.c"
// #include "window.c"

void	exit_game(t_data *data)
{
	free(data->north_texture);
	free(data->west_texture);
	free(data->east_texture);
	free(data->south_texture);
	free(data->map);
	free(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	
	exit(0);
}

void	init_data(t_data *data)
{
	data->block_size = 50;
	data->player_a = 0;
	data->player_y = 0;
	data->player_x = 0;
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
	get_map(argv[argc - 1], data);
	printf("playery y: %f\n", data->player_y);
	printf("playery x: %f\n", data->player_x);
	data->map_size = data->map_y * data->map_x;
	load_textures(data);
	window_loop(data);
	
}
