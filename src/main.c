/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2025/02/14 15:09:16 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	main(int argc, char **argv)
{
	t_data			*data;
	
	if (argc == 1)
		return(write(STDERR_FILENO, "Specify map to read\n", 21));
	if (argc == 3)
		return(write(STDERR_FILENO, "Too many arguments\n", 20));
    data = malloc(sizeof(t_data));
	data->block_size = 50;
	get_map(argv[argc - 1], data);
	printf("playery y: %f\n", data->player_y);
	printf("playery x: %f\n", data->player_x);
	
	data->map_size = data->map_y * data->map_x;
	// to free block
	free(data->north_texture);
	free(data->west_texture);
	free(data->east_texture);
	free(data->south_texture);
	free(data->map);
	free(data);
	//
	exit(1);
	window_loop(data);
}
