/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/08 19:50:18 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// map will be first parsed into array of strings
// the amount of strings is map_y
// the longest string is map_x
// spaces will be converted into walls
// tabs into 4 walls
// player_a will depend on wether is N, W, E ,S is player

inline unsigned int rgb_to_hex(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

char *get_map(char *map_path, t_data *data)
{
	int fd = open(map_path, O_RDONLY);
	char *config[6];

	if (fd == -1)
		exit(write(2, "could not open the file\n", 25));
	
	config[0] = get_next_line(fd);
	config[1] = get_next_line(fd);
	config[2] = get_next_line(fd);
	config[3] = get_next_line(fd);
	config[4] = get_next_line(fd);
	config[5] = get_next_line(fd);
	
}
