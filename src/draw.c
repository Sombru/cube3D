/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:26:19 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/09 19:26:47 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// cast a ray from player and return distance to the wall. Changed to float to return distance
float	cast_ray(t_data *data, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	ray_dx;
	float	ray_dy;
	int		hit;
	float	distance;

	ray_x = data->player_x;
	ray_y = data->player_y;
	ray_dx = cos(ray_angle);
	ray_dy = sin(ray_angle);
	int map_x, map_y;
	hit = 0;
	distance = 0;
	while (!hit)
	{
		ray_x += ray_dx;
		ray_y += ray_dy;
		distance += 1;
		map_x = (int)(ray_x / data->block_size);
		map_y = (int)(ray_y / data->block_size);
		if (map_x >= 0 && map_x < data->map_x && map_y >= 0
			&& map_y < data->map_y)
		{
			if (data->map[map_y * data->map_x + map_x] == 1)
			{
				hit = 1;
			}
		}
		else
		{
			hit = 1;
		}
	}
	return (distance * cos(ray_angle - data->player_a));
	// distance * cos(ray_angle - data->player_a) to fix fish eye effect
}

void	draw_rays(t_data *data)
{
	float	fov;
	float	angle_step;
	float	start_angle;
	float	ray_angle;
	int		i;

	fov = PI / 2;
	angle_step = fov / NUM_OF_RAYS;
	start_angle = data->player_a - (fov / 2);
	i = 0;
	while (i < NUM_OF_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		cast_ray(data, ray_angle);
		i++;
	}
}

void	pixel_to_frame(t_data *data, int x, int y, int color, int is_3d)
{
    char	*dst;

    if (is_3d)
        dst = data->addr_3d + (y * data->line_length + x * (data->bits_per_pixel / 8));
    else
        dst = data->addr_2d + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


// https://www.youtube.com/watch?v=CceepU1vIKo&t=18s
// we use abs of x0, x1 and y0, y1 to get absolute diference in coordinates
void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color, int is_3d)
{
    int	delta_x;
    int	delta_y;
    int	step_x;
    int	step_y;
    int	D2;
    int	D;

    delta_x = abs(x1 - x0);
    delta_y = abs(y1 - y0);
    D = delta_x - delta_y;
    if (x0 < x1)
        step_x = 1;
    else
        step_x = -1;
    if (y0 < y1)
        step_y = 1;
    else
        step_y = -1;
    while (1)
    {
        pixel_to_frame(data, x0, y0, color, is_3d);
        if (x0 == x1 && y0 == y1)
            break ;
        D2 = D * 2;
        if (D2 > -delta_y)
        {
            D -= delta_y;
            x0 += step_x;
        }
        if (D2 < delta_x)
        {
            D += delta_x;
            y0 += step_y;
        }
    }
}

#include "../includes/cube3D.h"

int	draw_player(t_data *data)
{
    int x, y;
    int size = 10; // Size of the player
    y = data->player_y;
    while (y < data->player_y + size)
    {
        x = data->player_x;
        while (x < data->player_x + size)
        {
            pixel_to_frame(data, x, y, GREEN, 0); // 0 for 2D
            x++;
        }
        y++;
    }
    return (0);
}

int	draw_map(t_data *data)
{
    int	color;
    int	start_x;
    int	start_y;
    int	end_x;
    int	end_y;
    int	i;
    int	j;

    int x, y;
    y = 0;
    while (y < data->map_y)
    {
        x = 0;
        while (x < data->map_x)
        {
            if (data->map[y * data->map_x + x] == 1)
                color = WHITE; // Wall
            else
                color = BLACK; // Empty space
            start_x = x * data->block_size + 1;
            start_y = y * data->block_size + 1;
            end_x = start_x + data->block_size - 1;
            end_y = start_y + data->block_size - 1;
            i = start_y;
            while (i < end_y)
            {
                j = start_x;
                while (j < end_x)
                {
                    pixel_to_frame(data, j, i, color, 0); // 0 for 2D
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
    return (0);
}

void	draw_direction(t_data *data)
{
    int	ray_length;
    int	end_x;
    int	end_y;

    ray_length = 100;
    end_x = data->player_x + (data->player_d_x) * ray_length;
    end_y = data->player_y + (data->player_d_y) * ray_length;
    // x + 5 && y + 5 to center the ray around player
    draw_line(data, data->player_x + 5, data->player_y + 5, end_x, end_y, GREEN, 0); // 0 for 2D
}

void	render_3D(t_data *data)
{
    float start_angle;
    float ray_angle;
    float distance;
    int wall_height;
    int wall_start;
    int wall_end;

    float fov = PI / 3; // 60 degrees
    float angle_step = fov / data->screen_width;
    start_angle = data->player_a - (fov / 2);
    int x = 0;
    while (x < data->screen_width)
    {
        ray_angle = start_angle + x * angle_step; // angle of the ray
        distance = cast_ray(data, ray_angle);
        wall_height = (BLOCK_SIZE * data->screen_height) / distance; // calc wall height
        if (wall_height > data->screen_height)
            wall_height = data->screen_height; // cap max height
        wall_start = (data->screen_height / 2) - (wall_height / 2); // center the wall
        wall_end = (data->screen_height / 2) + (wall_height / 2);
        int y = 0;
        while (y < data->screen_height)
        {
            if (y < wall_start)
                pixel_to_frame(data, x, y, 0x87CEEB, 1); // sky, 1 for 3D
            else if (y >= wall_start && y <= wall_end)
                pixel_to_frame(data, x, y, 0xA52A2A, 1); // wall, 1 for 3D
            else
                pixel_to_frame(data, x, y, 0x228B22, 1); // floor, 1 for 3D
            y++;
        }
        x++;
    }
}