/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 13:28:55 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 13:30:08 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	pixel_to_frame_2d(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_2d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	pixel_to_frame_3d(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr_3d + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	calculate_wall_dimensions(t_data *data, float distance,
		t_wall_dims *dims)
{
	dims->real_height = (data->block_size * data->screen_height) / distance;
	dims->start_unclamped = (data->screen_height - dims->real_height) / 2;
	dims->height = (int)dims->real_height;
	if (dims->height > data->screen_height)
		dims->height = data->screen_height;
	dims->start = (data->screen_height - dims->height) / 2;
	dims->end = dims->start + dims->height;
}
