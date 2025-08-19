/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:12 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/13 15:02:14 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_exit_hook(int key, t_vars *vars);

void	set_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win, key_exit_hook, vars);
	mlx_hook(vars->win, 17, 0, mlx_loop_end, vars->mlx);
}

static int	key_exit_hook(int key, t_vars *vars)
{
	if (key == ESCAPE)
		mlx_loop_end(vars->mlx);
	return (EXIT_SUCCESS);
}
