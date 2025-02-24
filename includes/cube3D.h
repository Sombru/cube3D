/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:56 by sombru            #+#    #+#             */
/*   Updated: 2025/02/24 13:55:35 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft_based/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x228B22
# define BLUE 0x87CEEB
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define GRAY 0x808080
# define LIGHT_GRAY 0xD3D3D3
# define DARK_GRAY 0xA9A9A9
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define PURPLE 0x800080
# define BROWN 0xA52A2A

# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define SPACE 32
# define ESCAPE 65307

# define PI 3.1415926535897932384
# define FOV (PI / 3)
# define HALF_FOV (FOV / 2)
# define RIGHT_SIDE_START (PI / 2)
# define RIGHT_SIDE_END (3 * PI / 2)
# define NUM_OF_RAYS 40
# define DEBUG_MODE 0

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
	float		player_x;
	float		player_y;
	float		player_d_x;
	float		player_d_y;
	float		player_a;
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

int				action(int keycode, t_data *data);

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
void			load_textures(t_data *data);

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
