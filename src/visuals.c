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

bool	set_visuals(t_vars *vars, t_data *img)
{	
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (false);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->win)
	{
		free_visuals(vars, NULL);
		return (false);
	}
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!img->img)
	{
		free_visuals(vars, NULL);
		return (false);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
	return (true);
}

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

void	free_visuals(t_vars *vars, t_data *img)
{
	if (img != NULL)
		mlx_destroy_image(vars->mlx, img->img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}
