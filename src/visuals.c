/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:12 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 18:07:38 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	set_visuals(t_vars *vars, t_data *data)
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
	data->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		free_visuals(vars, NULL);
		return (false);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
//	printf("img adress: %p\n", data->addr);//REMOVE
	return (true);
}

void	free_visuals(t_vars *vars, t_data *data)
{
	if (data != NULL)
		mlx_destroy_image(vars->mlx, data->img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	ft_mlx_put_pixel(t_data *data, t_point point)
{
	char	*dst;

	if (point.x >= 0 && point.x < WIDTH && point.y >= 0 && point.y < HEIGHT)
	{
		dst = data->addr + (point.y * data->line_length + point.x
				* (data->bits_per_pixel / 8));
		*(unsigned int *) dst = point.color;
	}
}
