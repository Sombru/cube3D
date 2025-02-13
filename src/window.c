/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/13 16:31:17 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	window_loop(t_data *data)
{
	data->mlx = mlx_init();
	data->screen_width = 1440;
	data->screen_height = 720;
	data->win_2d = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cube3D - 2D View");
	data->win_3d = mlx_new_window(data->mlx, data->screen_width,
			data->screen_height, "Cube3D - 3D View");
	data->frame_2d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	data->frame_3d = mlx_new_image(data->mlx, data->screen_width,
			data->screen_height);
	data->player_x = 100;
	data->player_y = 100;
	mlx_hook(data->win_2d, 2, 1L << 0, action, data);
	mlx_hook(data->win_3d, 2, 1L << 0, action, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

int	render_frame(t_data *data)
{
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
	draw_direction(data);
	draw_rays(data);
	render_3D(data);
	mlx_put_image_to_window(data->mlx, data->win_2d, data->frame_2d, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_3d, 0, 0);
	return (0);
}
