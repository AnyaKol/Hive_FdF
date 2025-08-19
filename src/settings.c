/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:33:29 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 11:14:21 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_rotation(t_map *map, float xy, float zy)
{
	map->angle_xy = xy;
	map->angle_zy = zy;
	map->offset_x = ((map->cols - map->rows) * cos(xy)) / 2;
	map->offset_y = ((map->rows + map->cols) * sin(zy)) / 2;
}

void	set_map_zoom(t_map *map, int zoom)
{
	int	width;
	int	height;

	width = (map->cols + map->rows) * cos(M_PI / 6) + 1;
	height = (map->cols + map->rows) * sin(M_PI / 6) + 2 * abs(map->peak) + 1;
	if (zoom == 0 || width > WIDTH / zoom)
		zoom = WIDTH / width;
	if (zoom == 0 || height > HEIGHT / zoom)
		zoom = HEIGHT / height;
	if (zoom == 0)
		zoom = 1;
	map->zoom = zoom;
}
