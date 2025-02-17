/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nspalevi <nspalevi@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:56 by sombru            #+#    #+#             */
/*   Updated: 2025/02/17 13:36:56 by nspalevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft_based/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
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
# define NUM_OF_RAYS 400
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
	float		player_d_x; // delta x of player
	float		player_d_y; // delta y of player
	float		player_a; // angle of a player
	int			*map;
	int			map_x;
	int			map_y;
	int			map_size;
	int			block_size;
	int			screen_width;
	int			screen_height;
	t_texture	textures[4];
}				t_data;

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

//===============================raycast=================================//

float			cast_ray(t_data *data, float ray_angle, int *side, float *hit_x,
					float *hit_y);
void			draw_rays(t_data *data);

//===============================render==================================//

void			render_3D(t_data *data);

//===============================window==================================//

void			window_loop(t_data *data);
int				render_frame(t_data *data);
void			load_textures(t_data *data);

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
//   dooors
//   collision
