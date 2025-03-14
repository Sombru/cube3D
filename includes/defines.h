/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 06:41:30 by sombru            #+#    #+#             */
/*   Updated: 2025/03/14 12:10:00 by pkostura         ###   ########.fr       */
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
# define SPACE 32
# define ESCAPE 65307

# define PI 3.1415926535897932384
# define FOV (PI / 3)
# define HALF_FOV (FOV / 2)
# define RIGHT_SIDE_START (PI / 2)
# define RIGHT_SIDE_END (3 * PI / 2)
# define NUM_OF_RAYS 40 // how detailed is view 

# define STEP 2 // how far to move per action
# define ANGLE_DIFF 0.05 // change of camera view per action
# define DOOR_RANGE 30.f // how far can we open door from 

# define DEBUG_MODE 1

#endif