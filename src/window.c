/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:31:30 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/21 17:25:35 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// window_loop:
// Initializes the window system by setting the screen dimensions,
// creating 2D and 3D windows and image buffers, setting the player’s initial position,
// and registering event hooks before starting the main loop.
void	window_loop(t_data *data)
{
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


// render_frame:
// Called on each frame; it destroys previous images, creates new ones,
// retrieves the image data addresses, calls all drawing functions to render
// the 2D map, player, rays, and direction, then displays the resulting images.
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
	draw_rays(data);
	draw_direction(data);
	render_3D(data);
	mlx_put_image_to_window(data->mlx, data->win_2d, data->frame_2d, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win_3d, data->frame_3d, 0, 0);
	return (0);
}

// load_textures:
// Loads the textures from XPM files, converts them into data arrays,
// and stores the image pointers, dimensions, and pixel data in the textures array.
void	load_textures(t_data *data)
{
	char cwd[1024];
	if (DEBUG_MODE)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			fprintf(stdout, "Current working dir: %s\n", cwd);
		else
			perror("getcwd() error");
	}

	data->textures[0].img = mlx_xpm_file_to_image(data->mlx, "texture/catvape.xpm", &data->textures[0].width, &data->textures[0].height);
	if (!data->textures[0].img)
	{
		fprintf(stderr, "Error loading texture 1\n");
		exit(EXIT_FAILURE);
	}
	data->textures[0].data = (int *)mlx_get_data_addr(data->textures[0].img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (DEBUG_MODE)
		fprintf(stdout, "Texture 1 loaded: %p\n", data->textures[0].data);

	data->textures[1].img = mlx_xpm_file_to_image(data->mlx,
			"texture/catcake.xpm", &data->textures[1].width,
			&data->textures[1].height);
	if (!data->textures[1].img)
	{
		fprintf(stderr, "Error loading texture 2\n");
		exit(EXIT_FAILURE);
	}
	data->textures[1].data = (int *)mlx_get_data_addr(data->textures[1].img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (DEBUG_MODE)
		fprintf(stdout, "Texture 2 loaded: %p\n", data->textures[1].data);

	data->textures[2].img = mlx_xpm_file_to_image(data->mlx,
			"texture/catbird.xpm", &data->textures[2].width,
			&data->textures[2].height);
	if (!data->textures[2].img)
	{
		fprintf(stderr, "Error loading texture 3\n");
		exit(EXIT_FAILURE);
	}
	data->textures[2].data = (int *)mlx_get_data_addr(data->textures[2].img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (DEBUG_MODE)
		fprintf(stdout, "Texture 3 loaded: %p\n", data->textures[2].data);

	data->textures[3].img = mlx_xpm_file_to_image(data->mlx,
			"texture/ballsbird.xpm", &data->textures[3].width,
			&data->textures[3].height);
	if (!data->textures[3].img)
	{
		fprintf(stderr, "Error loading texture 4\n");
		exit(EXIT_FAILURE);
	}
	data->textures[3].data = (int *)mlx_get_data_addr(data->textures[3].img,
			&data->bits_per_pixel, &data->line_length, &data->endian);
	if (DEBUG_MODE)
		fprintf(stdout, "Texture 4 loaded: %p\n", data->textures[3].data);
}
