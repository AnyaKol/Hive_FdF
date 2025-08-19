/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:13 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	t_data	data;

	if (!set_visuals(&vars, &data))
	{
		free_map(map);
		print_error_and_exit("Failed to open window\n");
	}
	set_hooks_bonus(&vars, &data, map);
	//ft_printf(STDOUT, "bit per pixel: %i\n", data.bits_per_pixel);//REMOVE
	draw_map(&data, map);
	//ft_printf(STDOUT, "map zoom: %i\n", map->zoom);//REMOVE
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx);
	free_visuals(&vars, &data);
	free_map(map);
}
