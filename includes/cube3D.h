/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:56 by sombru            #+#    #+#             */
/*   Updated: 2025/03/10 07:02:17 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft_based/libft.h"
# include "../minilibx-linux/mlx.h"
# include "defines.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_player
{
	float		x;
	float		y;
	float		d_x;
	float		d_y;
	float		a;
	int			size;
}				t_player;

typedef struct	s_keys
{
    int	space;
    int	a;
    int	w;
    int	d;
    int	s;
    int	left;
    int	right;
}				t_keys;

typedef struct s_texture
{
	void		*img;
	int			*data;
	int			width;
	int			height;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win_2d;
	void		*win_3d;
	void		*frame_2d;
	void		*frame_3d;
	char		*addr_2d;
	char		*addr_3d;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			ceiling_color;
	int			floor_color;
	char		*map;
	int			map_x;
	int			map_y;
	int			map_size;
	int			block_size;
	int			minimap_size;
	int			screen_width;
	int			screen_height;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_player	player;
	t_keys		keys;
	t_texture	north;
	t_texture	east;
	t_texture	south;
	t_texture	west;
	t_texture	door;
	int			door_timer;
	char		*original_map;
	int			off_x;
	int			off_y;
	float		start_angle;
	float		angle_step;
	int			scaled_size;
}				t_data;

//===============================main==================================//

void			exit_game(t_data *data);

//===============================debug==================================//

void			debug_map(char **map, t_data *data);

//===============================action==================================//

int				action(t_data *data);
int				key_press_handler(int keycode, t_data *data);
int				key_release_handler(int keycode, t_data *data);

//================================draw===================================//

void			pixel_to_frame(t_data *data, int x, int y, int color,
					int is_3d);
int				draw_player(t_data *data);
int				draw_map(t_data *data);
void			draw_direction(t_data *data);
void			draw_line(t_data *data, int x0, int y0, int x1, int y1,
					int color, int is_3d);
int				scale_block_size(t_data *data);
void			get_map_offsets(t_data *data, int block_size, int *off_x,
					int *off_y);

//===============================raycast=================================//

float			cast_ray(t_data *data, float ray_angle, int *side, float *hit_x,
					float *hit_y, char *hit_cell);
void			draw_rays(t_data *data);

//===============================render==================================//

void			render_3D(t_data *data);

//===============================window==================================//

void			window_loop(t_data *data);
int				render_frame(t_data *data);

//===============================parse_map====================================//

void			get_map(char *map_path, t_data *data);

//===============================parsing_utils================================//

void			free_config(t_data *data);
void			free_gnl_buffer(int fd);
int				is_valid_map_line(char *map_line);
void			safe_exit(int fd, char **map, t_data *data,
					const char *message);

//===============================get_config===================================//

void			get_player_pos(int fd, char **map_parse, t_data *data);
void			is_map_closed(int fd, char **map, t_data *data);

//===============================get_map_config===============================//

int				get_config(int fd, t_data *data);
int				get_colors(char *line, const char type, t_data *data);
int				get_textures(char *line, const char type, t_data *data);

#endif

// + have a working window
// + have a drawn map and player
// + have all rendered frame by frame instead of pixel by pixel
//   read a map from a file
//		validate map from a file
// + render all in 3D
// ~ minimap (prob use existing window and fust draw game in new window)
//   mouse view (prob only with X axis since idk how render it in Y)
//   animted sprite
// + dooors
// + collision
