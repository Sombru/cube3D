/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 13:30:05 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

static void	init_ray_values(t_data *data, int i, t_ray_params *ray,
		float *distance)
{
	*ray = create_ray_params(data->start_angle + i * data->angle_step);
	*distance = cast_ray(data, ray);
	if (*distance < 0.001)
		*distance = 0.001;
}

static t_texture	*select_texture(t_data *data, t_ray_params ray)
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

static void	calculate_texture_x(t_data *data, t_ray_params ray, t_texture *tex,
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

static void	draw_wall_section(t_data *data, t_draw_params *p, int y)
{
	float	tex_pos;
	int		tex_y;
	int		color;

	if (y >= data->screen_height)
		return ;
	if (y < p->wall_start)
		pixel_to_frame_3d(data, p->x, y, BLUE);
	else if (y > p->wall_end)
		pixel_to_frame_3d(data, p->x, y, GREEN);
	else
	{
		tex_pos = (y - p->start_unclamped) / p->wall_height;
		tex_y = (int)(tex_pos * p->tex->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= p->tex->height)
			tex_y = p->tex->height - 1;
		color = p->tex->data[tex_y * p->tex->width + p->tex_x];
		pixel_to_frame_3d(data, p->x, y, color);
	}
	draw_wall_section(data, p, y + 1);
}

void	render_3d(t_data *data)
{
	t_ray_params	ray;
	float			distance;
	t_wall_dims		dims;
	t_draw_params	params;
	int				i;

	data->angle_step = FOV / data->screen_width;
	data->start_angle = data->player.a - HALF_FOV;
	i = 0;
	while (i < data->screen_width)
	{
		init_ray_values(data, i, &ray, &distance);
		calculate_wall_dimensions(data, distance, &dims);
		params.x = i;
		params.wall_start = dims.start;
		params.wall_end = dims.end;
		params.start_unclamped = dims.start_unclamped;
		params.wall_height = dims.real_height;
		params.tex = select_texture(data, ray);
		calculate_texture_x(data, ray, params.tex, &params.tex_x);
		draw_wall_section(data, &params, 0);
		i++;
	}
}
