/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/13 18:22:09 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	visuals_loop(t_map *map);
void	draw_map(t_data *img, t_map *map);
void	draw_pixels(t_data *img, int x, int y);

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
	int	x;
	int	y;

	ft_printf(STDOUT, "rows: %i, cols: %i\n", map->rows, map->cols);//REMOVE
	i = 0;
	printf("angle xy: %f, angle zy: %f\n", map->angle_xy, map->angle_zy);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			x = (j + i * sin(map->angle_xy)) * 50;
			y = (map->peak - map->values[i][j] + i * sin(map->angle_zy)) * 50;
			x += WIDTH / 2 - map->offset_x * 50;
			y += HEIGHT / 2 - map->offset_y * 50;
			draw_pixels(img, x, y);
			j++;
		}
		i++;
	}
}

void	draw_pixels(t_data *img, int x, int y)
{
	ft_mlx_put_pixel(img, x, y, 0x00FFFFFF);
	ft_mlx_put_pixel(img, x + 1, y, 0x00FFFFFF);
	ft_mlx_put_pixel(img, x, y + 1, 0x00FFFFFF);
	ft_mlx_put_pixel(img, x + 1, y + 1, 0x00FFFFFF);
}
