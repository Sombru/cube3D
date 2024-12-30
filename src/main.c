/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:21:28 by sombru            #+#    #+#             */
/*   Updated: 2024/12/30 20:12:28 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	close_win(int keycode, t_vars *vars)
{
	keycode = keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1440, 720, "Hello world!");
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx);
}
