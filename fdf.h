/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:25:34 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/15 17:15:03 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1920
# define HEIGHT 1080
# define STDOUT 1
# define STDERR 2
# define ESCAPE 0xFF1B
# define MOUSE_LEFT 0x0001

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

# include <stdio.h>//REMOVE

typedef enum	e_level
{
	HIGH = 0,
	MIDDLE,
	LOW,
}	t_level;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_map
{
	int		cols;
	int		rows;
	int		**values;
	int		peak;
	int		offset_x;
	int		offset_y;
	double	angle_xy;
	double	angle_zy;
	int		zoom;
}	t_map;

typedef struct s_point
{
	int		x;
	int		y;
	float	height;
}	t_point;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	check_args(int argc, char **argv, t_map *map);
void	clean_up(char *line, int fd);
bool	set_visuals(t_vars *vars, t_data *img);
void	set_hooks(t_vars *vars);
void	free_visuals(t_vars *vars, t_data *img);
void	fill_map(char *file, t_map *map);
void	free_map(t_map *map);
void	draw_map(t_data *img, t_map *map);
int		calculate_color(float height);
void	set_map_rotation(t_map *map, double xy, double zy);
void	set_map_zoom(t_map *map, int zoom);
void	ft_mlx_put_pixel(t_data *data, t_point point);
int		sign(int num);

#endif
