/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/14 17:46:49 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	visuals_loop(t_map *map);
void	draw_map(t_data *img, t_map *map);
void	draw_pixels(t_data *img, t_point point);
t_point	calculate_point(t_map *map, int i, int j);
void	draw_line(t_data *img, t_point a, t_point b);
void	draw_line_low(t_data *img, t_point dif, t_point index, t_point line);
void	draw_line_high(t_data *img, t_point dif, t_point index, t_point line);

int	main(int argc, char **argv)
{
	t_map	map;

	check_args(argc, argv, &map);
	fill_map(argv[1], &map);
	visuals_loop(&map);
	return (EXIT_SUCCESS);
}

void	visuals_loop(t_map *map)
{
	t_vars	vars;
	t_data	img;

	if (!set_visuals(&vars, &img))
	{
		free_map(map);
		ft_printf(STDERR, "Failed to open window\n");
		exit(EXIT_FAILURE);
	}
	set_hooks(&vars);
	draw_map(&img, map);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	free_visuals(&vars, &img);
	free_map(map);
}

void	draw_map(t_data *img, t_map *map)
{
	int	i;
	int	j;
	t_point	point;

//	ft_printf(STDOUT, "rows: %i, cols: %i\n", map->rows, map->cols);//REMOVE
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			point = calculate_point(map, i, j);
			ft_mlx_put_pixel(img, point);
			if (j > 0)
				draw_line(img, calculate_point(map, i, j - 1), point);
			if (i > 0)
				draw_line(img, calculate_point(map, i - 1, j), point);
			j++;
		}
		i++;
	}
}

t_point	calculate_point(t_map *map, int i, int j)
{
	t_point	point;

	point.x = (j - i) * cos(map->angle_xy) * 50;
	point.y = ((j + i) * sin(map->angle_zy) - map->values[i][j]) * 50;
	point.x += WIDTH / 2 - map->offset_x * 50;
	point.y += HEIGHT / 2 - map->offset_y * 50;
	point.color = 0x00FFFFFF;
	return (point);
}

void	draw_line(t_data *img, t_point a, t_point b)
{
	t_point	dif;
	t_point	index;

	dif.x = abs(b.x - a.x);
	dif.y = abs(b.y - a.y);
	dif.color = abs(b.color - a.color);
	index.x = (b.x - a.x) / dif.x;
	index.y = (b.y - a.y) / dif.y;
	index.color = (b.color - a.color) / dif.color;
	if (abs(dif.x) > abs(dif.y))
		draw_line_low(img, dif, index, a);
	else
		draw_line_high(img, dif, index, a);
}

void	draw_line_low(t_data *img, t_point dif, t_point index, t_point line)
{
	int	deriv;
	int	end;

	end = line.x + dif.x * index.x;
	deriv = 2 * dif.y - dif.x;
	while (line.x != end)
	{
		ft_mlx_put_pixel(img, line);
		if (deriv * index.y > 0)
		{
			line.y += index.y;
			deriv -= 2 * dif.x;
		}
		deriv += 2 * dif.y;
		line.x += index.x;
	}
}

void	draw_line_high(t_data *img, t_point dif, t_point index, t_point line)
{
	int	deriv;
	int	end;

	end = line.y + dif.y * index.y;
	deriv = 2 * dif.x - dif.y;
	while (line.y != end)
	{
		ft_mlx_put_pixel(img, line);
		if (deriv > 0)
		{
			line.x += index.x;
			deriv -= 2 * dif.y;
		}
		deriv += 2 * dif.x;
		line.y += index.y;
	}
}
