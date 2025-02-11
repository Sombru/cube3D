/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/11 13:42:35 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	window_loop(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_x * data->block_size,
			data->map_y * data->block_size, "Cube3D");
	data->frame = mlx_new_image(data->mlx, data->map_x * data->block_size,
			data->map_y * data->block_size);

	mlx_hook(data->win, 2, 1L << 0, action, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}

int	render_frame(t_data *data)
{
	mlx_destroy_image(data->mlx, data->frame);
	data->frame = mlx_new_image(data->mlx, data->map_x * data->block_size,
			data->map_y * data->block_size);
	data->addr = mlx_get_data_addr(data->frame, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data);
	draw_player(data);
	draw_direction(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->frame, 0, 0);
	return (0);
}
