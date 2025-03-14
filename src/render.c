/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:09:00 by nspalevi          #+#    #+#             */
/*   Updated: 2025/03/14 15:17:11 by nspalevi         ###   ########.fr       */
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

static void	draw_wall_section(t_data *data, t_drawing *draw, int y)
{
	float	tex_pos;
	int		tex_y;
	int		color;

	if (y >= data->screen_height)
		return ;
	if (y < draw->wall_start)
		pixel_to_frame_3d(data, draw->x0, y, data->ceiling_color);
	else if (y > draw->wall_end)
		pixel_to_frame_3d(data, draw->x0, y, data->floor_color);
	else
	{
		tex_pos = (y - draw->start_unclamped) / draw->wall_height;
		tex_y = (int)(tex_pos * draw->tex->height);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= draw->tex->height)
			tex_y = draw->tex->height - 1;
		color = draw->tex->data[tex_y * draw->tex->width + draw->tex_x];
		pixel_to_frame_3d(data, draw->x0, y, color);
	}
	draw_wall_section(data, draw, y + 1);
}

void	render_3d(t_data *data)
{
	t_ray		ray;
	float		distance;
	t_wall_dims	dims;
	t_drawing	draw;
	int			i;

	data->angle_step = FOV / data->screen_width;
	data->start_angle = data->player.a - HALF_FOV;
	i = 0;
	while (i < data->screen_width)
	{
		init_ray_values(data, i, &ray, &distance);
		calculate_wall_dimensions(data, distance, &dims);
		draw.x0 = i;
		draw.wall_start = dims.start;
		draw.wall_end = dims.end;
		draw.start_unclamped = dims.start_unclamped;
		draw.wall_height = dims.real_height;
		draw.tex = select_texture(data, ray);
		calculate_texture_x(data, ray, draw.tex, &draw.tex_x);
		draw_wall_section(data, &draw, 0);
		i++;
	}
}
