/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/15 16:47:51 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
