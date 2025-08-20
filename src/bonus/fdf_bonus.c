/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/20 13:13:59 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	visuals_loop(t_env *env);

int	main(int argc, char **argv)
{
	t_env	env;
	t_map	map;

	env.map = &map;
	check_args(argc, argv, env.map);
	fill_map(argv[1], env.map);
	visuals_loop(&env);
	return (EXIT_SUCCESS);
}

void	visuals_loop(t_env *env)
{
	t_vars	vars;
	t_data	data;

	env->vars = &vars;
	env->data = &data;
	if (!set_visuals(&vars, &data))
	{
		free_map(env->map);
		print_error_and_exit("Failed to open window\n");
	}
	set_hooks_bonus(env);
	draw_map(&data, env->map);
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);
	mlx_loop(vars.mlx);
	free_visuals(&vars, &data);
	free_map(env->map);
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
