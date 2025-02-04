/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:56 by sombru            #+#    #+#             */
/*   Updated: 2025/02/04 17:07:18 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft_based/libft.h"
# include "../minilibx-linux/mlx.h"

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

# define BLOCK_SIZE 50

struct s_ray;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	float		player_x;
	float		player_y;
	float		player_d_x; // delta x of player
	float		player_d_y; // delta y of player
	float		player_a; // angle of a player
	int			*map;
	int			map_x;
	int			map_y;
	int			map_size;
	int			cell_size;
}				t_data;

typedef struct s_ray
{
	int		ray;
	int		map_x;
	int		map_y;
	int		map_hit;
	int		dof;
	float	ray_x;
	float	ray_y;
	float	ray_a; // angle of ray
	float	offset_x;
	float	offset_y;
}				t_ray;


//===============================window==================================//

void    window_loop(t_data *data);

//================================draw===================================//

int		draw_player(t_data *data);
int		draw_map(t_data *data);
void	draw_direction(t_data *data);
void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color);
t_ray	*draw_rays(t_data *data);


//===============================action==================================//

int action(int keycode, t_data *data);

#endif