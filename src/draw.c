/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:17:33 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:49 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	calculate_point(t_map *map, int i, int j);
static void		draw_line(t_data *data, t_point a, t_point b);
static void		draw_line_low(t_data *data, t_point dif, t_point line);
static void		draw_line_high(t_data *data, t_point dif, t_point line);

void	draw_map(t_data *data, t_map *map)
{
	int		i;
	int		j;
	t_point	point;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			point = calculate_point(map, i, j);
			ft_mlx_put_pixel(data, point);
			if (j > 0)
				draw_line(data, calculate_point(map, i, j - 1), point);
			if (i > 0)
				draw_line(data, calculate_point(map, i - 1, j), point);
			j++;
		}
		i++;
	}
}

static t_point	calculate_point(t_map *map, int i, int j)
{
	t_point	point;

	point.height = 0;
	if (map->peak != 0)
		point.height = (float) map->values[i][j] / (float) abs(map->peak);
	point.x = (j - i) * cos(map->angle_xy) * map->zoom;
	point.y = ((j + i) * sin(map->angle_zy) - map->values[i][j]) * map->zoom;
	point.x += WIDTH / 2 - map->offset_x * map->zoom;
	point.y += HEIGHT / 2 - map->offset_y * map->zoom;
	point.color = map->colors[i][j];
	return (point);
}

static void	draw_line(t_data *data, t_point a, t_point b)
{
	t_point	dif;

	dif.x = b.x - a.x;
	dif.y = b.y - a.y;
	dif.height = b.height - a.height;
	if (a.color != NO_COLOR || b.color != NO_COLOR)
	{
		if (a.color == NO_COLOR)
			a.color = calculate_color(a.height, NO_COLOR, NO_COLOR);
		else if (b.color == NO_COLOR)
			b.color = calculate_color(b.height, NO_COLOR, NO_COLOR);
		a.height = 0;
		dif.height = 1;
	}
	dif.color = b.color;
	if (abs(dif.x) > abs(dif.y))
		draw_line_low(data, dif, a);
	else
		draw_line_high(data, dif, a);
}

static void	draw_line_low(t_data *data, t_point dif, t_point line)
{
	int	deriv;
	int	end;
	int	start_color;

	start_color = line.color;
	end = line.x + dif.x - sign(dif.x);
	deriv = 2 * abs(dif.y) - abs(dif.x);
	while (line.x != end)
	{
		if (deriv * sign(dif.y) > 0)
		{
			deriv -= 2 * abs(dif.x) * sign(dif.y);
			line.y += sign(dif.y);
		}
		deriv += 2 * abs(dif.y) * sign(dif.y);
		line.x += sign(dif.x);
		line.height += dif.height / abs(dif.x);
		line.color = calculate_color(line.height, start_color, dif.color);
		ft_mlx_put_pixel(data, line);
	}
}

static void	draw_line_high(t_data *data, t_point dif, t_point line)
{
	int	deriv;
	int	end;
	int	start_color;

	start_color = line.color;
	end = line.y + dif.y - sign(dif.y);
	deriv = 2 * abs(dif.x) - abs(dif.y);
	while (line.y != end)
	{
		if (deriv * sign(dif.x) > 0)
		{
			deriv -= 2 * abs(dif.y) * sign(dif.x);
			line.x += sign(dif.x);
		}
		deriv += 2 * abs(dif.x) * sign(dif.x);
		line.y += sign(dif.y);
		line.height += dif.height / abs(dif.y);
		line.color = calculate_color(line.height, start_color, dif.color);
		ft_mlx_put_pixel(data, line);
	}
}
