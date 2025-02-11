/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:56 by sombru            #+#    #+#             */
/*   Updated: 2025/02/11 13:31:42 by pkostura         ###   ########.fr       */
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
# include <fcntl.h>


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

# define NUM_OF_RAYS 40

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*frame;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	float	player_x;
	float	player_y;
	float	player_d_x; // delta x of player
	float	player_d_y; // delta y of player
	float	player_a;   // angle of a player
	char	*textures[4];
	int		ceiling_color;
	int		floor_color;
	char	*map;
	int		map_x;
	int		map_y;
	int		map_size;
	int		block_size;
}			t_data;

//===============================debug==================================//

void	debug_map(char	**map);

//===============================window==================================//

void		window_loop(t_data *data);
int			render_frame(t_data *data);

//================================draw===================================//

void		pixel_to_frame(t_data *data, int x, int y, int color);
int			draw_player(t_data *data);
int			draw_map(t_data *data);
void		draw_direction(t_data *data);
void		draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
void		draw_rays(t_data *data);
void		cast_ray(t_data *data, float ray_angle);

//===============================action==================================//

int			action(int keycode, t_data *data);

//===============================parse_map==================================//

char 		*get_map(char *map_path, t_data *data);


#endif


// + have a working window
// + have a drawn map and player
// + have all rendered frame by frame instead of pixel by pixel
//   read a map from a file
//	 validate map from a file
//   render all in 3D
//   minimap (prob use existing window and fust draw game in new window)
//   mouse view (prob only with X axis since idk how render it in Y)
//   animted sprite
//   dooors
//   collision