/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:17:33 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/14 20:53:42 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	calculate_point(t_map *map, int i, int j);
static void		draw_line(t_data *img, t_point a, t_point b);
static void		draw_line_low(t_data *img, t_point dif, t_point line);
static void		draw_line_high(t_data *img, t_point dif, t_point line);

void	draw_map(t_data *img, t_map *map)
{
	int	i;
	int	j;
	t_point	point;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
		//	ft_printf(STDOUT, " %i", map->values[i][j]);//REMOVE
			point = calculate_point(map, i, j);
			ft_mlx_put_pixel(img, point);
			if (j > 0)
				draw_line(img, calculate_point(map, i, j - 1), point);
			if (i > 0)
				draw_line(img, calculate_point(map, i - 1, j), point);
			j++;
		}
	//	ft_printf(STDOUT, "\n");//REMOVE
		i++;
	}
}

static t_point	calculate_point(t_map *map, int i, int j)
{
	t_point	point;

	point.x = (j - i) * cos(map->angle_xy) * map->zoom;
	point.y = ((j + i) * sin(map->angle_zy) - map->values[i][j]) * map->zoom;
	point.x += WIDTH / 2 - map->offset_x * map->zoom;
	point.y += HEIGHT / 2 - map->offset_y * map->zoom;
	if (map->values[i][j] >= 0)
		point.color = 0x0000FF00 + (ft_min(map->values[i][j], 127) << 16) - (ft_min(map->values[i][j], 127) << 8);
	else
		point.color = 0x0000FF00 + ft_min(-map->values[i][j], 127) - (ft_min(-map->values[i][j], 127) << 8);
//	ft_printf(STDOUT, "height: %i, color: %i\n", map->values[i][j], point.color);//REMOVE
	return (point);
}

static void	draw_line(t_data *img, t_point a, t_point b)
{
	t_point	dif;

	dif.x = b.x - a.x;
	dif.y = b.y - a.y;
	dif.color = b.color - a.color;
	if (abs(dif.x) > abs(dif.y))
		draw_line_low(img, dif, a);
	else
		draw_line_high(img, dif, a);
}

static void	draw_line_low(t_data *img, t_point dif, t_point line)
{
	int	deriv;
	int	end;

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
		line.color += dif.color / abs(dif.x);
		ft_mlx_put_pixel(img, line);
	}
}

static void	draw_line_high(t_data *img, t_point dif, t_point line)
{
	int	deriv;
	int	end;

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
		line.color += dif.color / abs(dif.y);
		ft_mlx_put_pixel(img, line);
	}
}
