/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/20 09:38:03 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// window_loop() - Sets up MLX windows and hooks for input/rendering
// render_frame() - Main rendering loop that updates door timer,
//	refreshes display buffers and redraws scene
// load_textures() - Loads wall and door textures from XPM files

void	window_loop(t_data *data)
{
	data->win_3d = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cube3D - 3D");
	data->frame_2d = mlx_new_image(data->mlx, data->minimap_size,
			data->minimap_size);
	data->frame_3d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	mlx_hook(data->win_3d, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->win_3d, 3, 1L << 1, key_release_handler, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

static void	handle_door_timer(t_data *data)
{
	int	total;
	int	i;

	if (data->door_timer > 0)
	{
		data->door_timer--;
		if (data->door_timer == 0)
		{
			total = data->map_x * data->map_y;
			i = 0;
			while (i < total)
			{
				if (data->original_map[i] == '2')
					data->map[i] = '2';
				i++;
			}
		}
	}
}

int	render_frame(t_data *data)
{
	handle_door_timer(data);
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
	render_3d(data);
	action(data);
	if (data->keys.m)
		mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_2d, 0, 0);
	else
		mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_3d, 0, 0);
	return (0);
}
