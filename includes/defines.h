/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:41:30 by sombru            #+#    #+#             */
/*   Updated: 2025/03/17 13:56:01 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

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
# define M_KEY 0x6d // using keysym cuz actual keycode doesnt work
# define SPACE 32
# define ESCAPE 65307

# define PI 3.1415926535897932384
# define FOV 1.0471975511965977461333333333333 // (PI / 3)
# define HALF_FOV 0.52359877559829887306666666666667 // (FOV / 2)
# define RIGHT_SIDE_START 1.5707963267948966192 //(PI / 2)
# define RIGHT_SIDE_END 4.7123889803846898576 //(3 * PI / 2)
# define NUM_OF_RAYS 10000 // how detailed is view 

# define STEP 2 // how far to move per action // keep less than BLOCK_SIZE
# define BLOCK_SIZE 50 // doesnt really affect much
# define SCREEN_WIDTH 1440
# define SCREEN_HEIGHT 720
# define MINIMAP_SIZE 1000 // not bigger than SCREEN_HEIGHT/SCREEN WITDH
# define ANGLE_DIFF 0.05 // change of camera view per action
# define DOOR_RANGE 30.f // how far can we open door from 

# define DEBUG_MODE 0

#endif