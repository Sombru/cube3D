/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/17 13:54:12 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static void	init_ray_values(t_data *data, int i, t_ray *ray, float *distance)
{
	*ray = create_ray(data->start_angle + i * data->angle_step);
	*distance = cast_ray(data, ray);
	if (*distance < 0.001)
		*distance = 0.001;
}

static t_texture	*select_texture(t_data *data, t_ray ray)
{
	if (ray.hit_cell == '2')
		return (&data->door);
	if (ray.side == 0)
	{
		if (cos(ray.ray_angle) > 0)
			return (&data->east);
		return (&data->west);
	}
	if (sin(ray.ray_angle) > 0)
		return (&data->south);
	return (&data->north);
}

static void	calculate_texture_x(t_data *data, t_ray ray, t_texture *tex,
		int *tex_x)
{
	float	hit_offset;

	if (ray.side == 0)
		hit_offset = fmodf(ray.hit_y, data->block_size);
	else
		hit_offset = fmodf(ray.hit_x, data->block_size);
	*tex_x = (int)((hit_offset / data->block_size) * tex->width);
	if (ray.side == 0 && ray.ray_angle > RIGHT_SIDE_START
		&& ray.ray_angle < RIGHT_SIDE_END)
		*tex_x = tex->width - *tex_x - 1;
	if (ray.side == 1 && ray.ray_angle < PI)
		*tex_x = tex->width - *tex_x - 1;
}

static void	process_ray(t_data *data, int i)
{
	t_ray		ray;
	float		distance;
	t_wall_dims	dims;
	t_drawing	draw;

	init_ray_values(data, i, &ray, &distance);
	calculate_wall_dimensions(data, distance, &dims);
	draw.tex = select_texture(data, ray);
	calculate_texture_x(data, ray, draw.tex, &draw.tex_x);
	draw.start_x = (i * data->screen_width) / NUM_OF_RAYS;
	draw.end_x = ((i + 1) * data->screen_width) / NUM_OF_RAYS;
	if (draw.end_x > data->screen_width)
		draw.end_x = data->screen_width;
	draw.current_x = draw.start_x;
	while (draw.current_x < draw.end_x)
	{
		draw.x0 = draw.current_x;
		draw.wall_start = dims.start;
		draw.wall_end = dims.end;
		draw.start_unclamped = dims.start_unclamped;
		draw.wall_height = dims.real_height;
		draw_wall_section(data, &draw, 0);
		draw.current_x++;
	}
}

void	render_3d(t_data *data)
{
	int	i;

	if (NUM_OF_RAYS > 0)
		data->angle_step = FOV / NUM_OF_RAYS;
	else
		data->angle_step = FOV;
	data->start_angle = data->player.a - HALF_FOV;
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		process_ray(data, i);
		i++;
	}
}
