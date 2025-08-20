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

static void	visuals_loop(t_map *map);

int	main(int argc, char **argv)
{
	t_map	map;

	check_args(argc, argv, &map);
	fill_map(argv[1], &map);
	visuals_loop(&map);
	return (EXIT_SUCCESS);
}

static void	visuals_loop(t_map *map)
{
	t_vars	vars;
	t_data	data;

	if (!set_visuals(&vars, &data))
	{
		free_map(map);
		print_error_and_exit("Failed to open window\n");
	}
	set_hooks(&vars);
	draw_map(&data, map);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx);
	free_visuals(&vars, &data);
	free_map(map);
}

int	print_error_and_return(char *str)
{
	int	len;

	if (ft_printf(STDERR, "%s", str) == ERROR)
	{
		len = ft_strlen(str);
		write(STDERR, "ft_printf error\n", 16);
		write(STDERR, str, len);
	}
	return (ERROR);
}

void	print_error_and_exit(char *str)
{
	print_error_and_return(str);
	exit(EXIT_FAILURE);
}
