/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/14 17:44:32 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_put_pixel(t_data *data, t_point point)
{
	char	*dst;

	if (point.x >= 0 && point.x < WIDTH && point.y >= 0 && point.y < HEIGHT)
	{
		dst = data->addr + (point.y * data->line_length
			+ point.x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = point.color;
	}
}

void	set_map_rotation(t_map *map, double xy, double zy)
{
	map->angle_xy = xy;
	map->angle_zy = zy;
	map->offset_x = ((map->cols - map->rows) * cos(xy)) / 2;
	map->offset_y = ((map->rows + map->cols) * sin(zy) - map->peak) / 2;
	map->zoom = 50;
}

int	sign(int num)
{
	return ((num > 0) - (num < 0));
}
