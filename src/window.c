/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/24 13:28:52 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	window_loop(t_data *data)
{
	data->win_2d = mlx_new_window(data->mlx, data->minimap_size,
			data->minimap_size, "Cube3D - 2D View");
	data->win_3d = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cube3D - 3D View");
	data->frame_2d = mlx_new_image(data->mlx, data->minimap_size,
			data->minimap_size);
	data->frame_3d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	mlx_hook(data->win_2d, 2, 1L << 0, action, data);
	mlx_hook(data->win_3d, 2, 1L << 0, action, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

// int	render_frame(t_data *data)
// {
// 	mlx_destroy_image(data->mlx, data->frame_2d);
// 	mlx_destroy_image(data->mlx, data->frame_3d);
// 	data->frame_2d = mlx_new_image(data->mlx, data->screen_width,
// 			data->screen_height);
// 	data->frame_3d = mlx_new_image(data->mlx, data->screen_width,
// 			data->screen_height);
// 	data->addr_2d = mlx_get_data_addr(data->frame_2d, &data->bits_per_pixel,
// 			&data->line_length, &data->endian);
// 	data->addr_3d = mlx_get_data_addr(data->frame_3d, &data->bits_per_pixel,
// 			&data->line_length, &data->endian);
// 	draw_map(data);
// 	draw_player(data);
// 	draw_rays(data);
// 	draw_direction(data);
// 	render_3D(data);
// 	mlx_put_image_to_window(data->mlx, data->win_2d, data->frame_2d, 0, 0);
// 	mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_3d, 0, 0);
// 	return (0);
// }

// void	load_textures(t_data *data)
// {
// 	data->north.img = mlx_xpm_file_to_image(data->mlx, "texture/catvape.xpm",
// 			&data->north.width, &data->north.height);
// 	if (!data->north.img)
// 	{
// 		fprintf(stderr, "Error loading north texture\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	data->north.data = (int *)mlx_get_data_addr(data->north.img,
// 			&data->bits_per_pixel, &data->line_length, &data->endian);
// 	if (DEBUG_MODE)
// 		fprintf(stdout, "North texture loaded: %p\n", data->north.data);
// 	data->east.img = mlx_xpm_file_to_image(data->mlx, "texture/catcake.xpm",
// 			&data->east.width, &data->east.height);
// 	if (!data->east.img)
// 	{
// 		fprintf(stderr, "Error loading east texture\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	data->east.data = (int *)mlx_get_data_addr(data->east.img,
// 			&data->bits_per_pixel, &data->line_length, &data->endian);
// 	if (DEBUG_MODE)
// 		fprintf(stdout, "East texture loaded: %p\n", data->east.data);
// 	data->south.img = mlx_xpm_file_to_image(data->mlx, "texture/catbird.xpm",
// 			&data->south.width, &data->south.height);
// 	if (!data->south.img)
// 	{
// 		fprintf(stderr, "Error loading south texture\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	data->south.data = (int *)mlx_get_data_addr(data->south.img,
// 			&data->bits_per_pixel, &data->line_length, &data->endian);
// 	if (DEBUG_MODE)
// 		fprintf(stdout, "South texture loaded: %p\n", data->south.data);
// 	data->west.img = mlx_xpm_file_to_image(data->mlx, "texture/ballsbird.xpm",
// 			&data->west.width, &data->west.height);
// 	if (!data->west.img)
// 	{
// 		fprintf(stderr, "Error loading west texture\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	data->west.data = (int *)mlx_get_data_addr(data->west.img,
// 			&data->bits_per_pixel, &data->line_length, &data->endian);
// 	if (DEBUG_MODE)
// 		fprintf(stdout, "West texture loaded: %p\n", data->west.data);
// }

int	render_frame(t_data *data)
{
	int	total;
	int	i;

	// Update door timer and revert any open door after 5 seconds (300 frames)
	if (data->door_timer > 0)
	{
		data->door_timer--;
		if (data->door_timer == 0)
		{
			total = data->map_x * data->map_y;
			i = 0;
			while (i < total)
			{
				// Restore door cell if originally door ('2')
				if (data->original_map[i] == '2')
					data->map[i] = '2';
				i++;
			}
		}
	}
	mlx_destroy_image(data->mlx, data->frame_2d);
	mlx_destroy_image(data->mlx, data->frame_3d);
	data->frame_2d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	data->frame_3d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	data->addr_2d = mlx_get_data_addr(data->frame_2d, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->addr_3d = mlx_get_data_addr(data->frame_3d, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data);
	draw_player(data);
	draw_rays(data);
	draw_direction(data);
	render_3D(data);
	mlx_put_image_to_window(data->mlx, data->win_2d, data->frame_2d, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_3d, 0, 0);
	return (0);
}

void	load_textures(t_data *data)
{
	// north face
	data->north.img = mlx_xpm_file_to_image(data->mlx, "texture/catvape.xpm",
			&data->north.width, &data->north.height);
	if (!data->north.img)
	{
		fprintf(stderr, "Error loading north texture\n");
		exit(EXIT_FAILURE);
	}
	data->north.data = (int *)mlx_get_data_addr(data->north.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	// east face
	data->east.img = mlx_xpm_file_to_image(data->mlx, "texture/catcake.xpm",
			&data->east.width, &data->east.height);
	if (!data->east.img)
	{
		fprintf(stderr, "Error loading east texture\n");
		exit(EXIT_FAILURE);
	}
	data->east.data = (int *)mlx_get_data_addr(data->east.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	// south face
	data->south.img = mlx_xpm_file_to_image(data->mlx, "texture/catbird.xpm",
			&data->south.width, &data->south.height);
	if (!data->south.img)
	{
		fprintf(stderr, "Error loading south texture\n");
		exit(EXIT_FAILURE);
	}
	data->south.data = (int *)mlx_get_data_addr(data->south.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	// west face
	data->west.img = mlx_xpm_file_to_image(data->mlx, "texture/ballsbird.xpm",
			&data->west.width, &data->west.height);
	if (!data->west.img)
	{
		fprintf(stderr, "Error loading west texture\n");
		exit(EXIT_FAILURE);
	}
	data->west.data = (int *)mlx_get_data_addr(data->west.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);

	// door texture
	data->door.img = mlx_xpm_file_to_image(data->mlx, "texture/wall.xpm",
			&data->door.width, &data->door.height);
	if (!data->door.img)
	{
		fprintf(stderr, "Error loading door texture\n");
		exit(EXIT_FAILURE);
	}
	data->door.data = (int *)mlx_get_data_addr(data->door.img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
}