/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 19:30:12 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_error(void);
void	exit_keyhook(mlx_key_data_t keydata, void *param);

int	main(int argc, char **argv)
{
	static mlx_image_t	*image;
	mlx_t	*mlx;
	t_map	map;

	check_args(argc, argv, &map);
	fill_map(argv[1], &map);
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		ft_error();
	image = mlx_new_image(mlx, 256, 256);
	if (!image || mlx_image_to_window(mlx, image, 0, 0) < 0)
		ft_error();
	mlx_key_hook(mlx, exit_keyhook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}



// Exit the program on 'Esc'
void	exit_keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(param);
}

// Exit the program as failure.
static void	ft_error(void)
{
	ft_printf(STDERR, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
