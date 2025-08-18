/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/18 19:53:26 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	visuals_loop(t_map *map);

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
		print_error_and_exit("Failed to open window\n");
	}
	set_hooks(&vars);
	draw_map(&img, map);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	free_visuals(&vars, &img);
	free_map(map);
}
