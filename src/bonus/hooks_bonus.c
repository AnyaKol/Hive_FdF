/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:12 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 19:33:57 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	key_exit_hook(int button, t_vars *vars);
static int	mouse_zoom_hook(int button, int x, int y, t_env *env);
void	change_zoom(int button, t_vars *vars, t_data *data, t_map *map);

void	set_hooks_bonus(t_vars *vars, t_data *data, t_map *map)
{
	t_env	env;

	env.vars = vars;
	env.data = data;
	env.map = map;
	ft_printf(STDOUT, "data addr: %p\n", env.data->addr);//REMOVE	
//	ft_printf(STDOUT, "map zoom heeere: %i\n", env.map->zoom);//REMOVE
	mlx_key_hook(env.vars->win, key_exit_hook, env.vars);
	mlx_mouse_hook(env.vars->win, mouse_zoom_hook, &env);
	mlx_hook(env.vars->win, ON_DESTROY, 0, mlx_loop_end, env.vars->mlx);
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
//	ft_printf(STDOUT, "mouse button %i at %ix%i\n", button, x, y);//REMOVE
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		change_zoom(button, env->vars, env->data, env->map);
//		env->map->zoom += 2;
//		if (env->map->zoom > 200)
//			env->map->zoom = 200;
//		ft_printf(STDOUT, "zoom mouse: %i\n", map_ptr->zoom);//REMOVE
		//redraw_map(env->vars, env->data, env->map);
	}
//	else if (button == SCROLL_DOWN)
//	{
//		env->map->zoom -= 2;
//		if (env->map->zoom < 1)
//			env->map->zoom = 1;
//		ft_printf(STDOUT, "zoom mouse down: %i\n", env->map->zoom);//REMOVE
		//redraw_map(env->vars, env->data, env->map);
//	}
	return (EXIT_SUCCESS);
}

void	change_zoom(int button, t_vars *vars, t_data *data, t_map *map)
{
	if (button == SCROLL_UP)
	{
//		env->map->zoom += 2;
//		if (env->map->zoom > 200)
//			env->map->zoom = 200;
		ft_printf(STDOUT, "zoom mouse up: %i\n", map->zoom);//REMOVE
		redraw_map(vars, data, map);
	}
//	else if (button == SCROLL_DOWN)
//	{
//		env->map->zoom -= 2;
//		if (env->map->zoom < 1)
//			env->map->zoom = 1;
//		ft_printf(STDOUT, "zoom mouse down: %i\n", env->map->zoom);//REMOVE
		//redraw_map(env->vars, env->data, env->map);
//	}
}

void	redraw_map(t_vars *vars, t_data *data, t_map *map)
{
	write(1, "here!\n", 6);
	ft_bzero(data->addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	draw_map(data, map);
	mlx_put_image_to_window(vars->mlx, vars->win, data->img, 0, 0);
}
