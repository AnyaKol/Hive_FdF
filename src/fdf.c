/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:30 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/12 19:59:59 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_visuals(t_map *map);
bool	create_visuals(t_vars *vars, t_data *img);
void	set_hooks(t_vars *vars);
int	key_exit_hook(int key, t_vars *vars);
void	free_visuals(t_vars *vars, t_data *img);
void	draw_map(t_data *img, t_map *map);
void	ft_mlx_put_pixel(t_data *data, int x, int y, int color);

int	main(int argc, char **argv)
{
	t_map	map;

	check_args(argc, argv, &map);
	fill_map(argv[1], &map);
	set_visuals(&map);
	return (EXIT_SUCCESS);
}

void	set_visuals(t_map *map)
{
	t_vars	vars;
	t_data	img;

	if (!create_visuals(&vars, &img))
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

bool	create_visuals(t_vars *vars, t_data *img)
{	
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (false);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		return (false);
	}
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!img->img)
	{
		free_visuals(vars, NULL);
		return (false);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
		&img->endian);
	return (true);
}

void	draw_map(t_data *img, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	ft_printf(STDOUT, "rows: %i, cols: %i\n", map->rows, map->cols);//REMOVE
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			ft_printf(STDOUT, " %i", map->values[i][j]);//REMOVE
			x = (j - cos(M_PI / 4) * i) * 50;
			y = (-map->values[i][j] / 5 + sin(M_PI / 4) * i) * 50;
			ft_mlx_put_pixel(img, x + WIDTH / 3, y + HEIGHT / 3, 0x00FFFFFF);
			ft_mlx_put_pixel(img, x + WIDTH / 3 + 1, y + HEIGHT / 3, 0x00FFFFFF);
			ft_mlx_put_pixel(img, x + WIDTH / 3, y + HEIGHT / 3 + 1, 0x00FFFFFF);
			ft_mlx_put_pixel(img, x + WIDTH / 3 + 1, y + HEIGHT / 3 + 1, 0x00FFFFFF);
			j++;
		}
		ft_printf(STDOUT, "\n");//REMOVE
		i++;
	}
}

void	set_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win, key_exit_hook, vars);
	mlx_hook(vars->win, 17, 0, mlx_loop_end, vars->mlx);
}

int	key_exit_hook(int key, t_vars *vars)
{
	if (key == ESCAPE)
		mlx_loop_end(vars->mlx);
	return (EXIT_SUCCESS);
}

void	free_visuals(t_vars *vars, t_data *img)
{
	if (img != NULL)
		mlx_destroy_image(vars->mlx, img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	ft_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}
