/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/02/09 15:05:13 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	
	// if (argc == 1)
		// return(write(STDERR_FILENO, "Specify map to read\n", 21));
	// if (argc == 2)
		// return(write(STDERR_FILENO, "Too many arguments\n", 21));
    data = malloc(sizeof(t_data));
	get_map(argv[argc - 1], data);
	data->map_size = 100;
	data->block_size = 50;
	data->player_d_x = cos(data->player_a);
	data->player_d_y = sin(data->player_a);
	exit(0);
	window_loop(data);
}
