/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:12 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/20 13:38:14 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	key_exit_hook(int button, t_vars *vars);
static int	mouse_zoom_hook(int button, int x, int y, t_env *env);

void	set_hooks_bonus(t_env *env)
{
	mlx_key_hook(env->vars->win, key_exit_hook, env->vars);
	mlx_mouse_hook(env->vars->win, mouse_zoom_hook, env);
	mlx_hook(env->vars->win, ON_DESTROY, 0, mlx_loop_end, env->vars->mlx);
}

static int	key_exit_hook(int button, t_vars *vars)
{
	if (button == ESCAPE)
		mlx_loop_end(vars->mlx);
	return (EXIT_SUCCESS);
}

static int	mouse_zoom_hook(int button, int x, int y, t_env *env)
{
	(void) x;
	(void) y;
	if (button == SCROLL_UP)
	{
		env->map->zoom += 2;
		if (env->map->zoom > 200)
			env->map->zoom = 200;
		redraw_map(env->vars, env->data, env->map);
	}
	else if (button == SCROLL_DOWN)
	{
		env->map->zoom -= 2;
		if (env->map->zoom < 1)
			env->map->zoom = 1;
		redraw_map(env->vars, env->data, env->map);
	}
	return (EXIT_SUCCESS);
}

void	redraw_map(t_vars *vars, t_data *data, t_map *map)
{
	ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	draw_map(data, map);
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}
