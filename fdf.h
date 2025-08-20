/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:25:34 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/20 13:41:04 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

# define STDOUT 1
# define STDERR 2

# define ERROR -1
# define SUCCESS 0
# define NO_COLOR 0

# define ESCAPE 0xFF1B
# define ON_DESTROY 17

# define BASE_HEX "0123456789ABCDEF"
# define BASE_HEX_LOW "0123456789abcdef"

# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef enum e_level
{
	HIGH = 0,
	MIDDLE,
	LOW,
}	t_level;

typedef struct s_map
{
	int		cols;
	int		rows;
	int		**values;
	int		**colors;
	int		peak;
	int		offset_x;
	int		offset_y;
	float	angle_xy;
	float	angle_zy;
	int		zoom;
}	t_map;

typedef struct s_point
{
	int		x;
	int		y;
	float	height;
	int		value;
	int		color;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

void	check_args(int argc, char **argv, t_map *map);
void	check_fd(int fd);
void	check_line(char *line, int fd, t_map *map);
int		skip_color(char *line);
int		get_color_from_arg(char *arg);
void	clean_up(char *line, int fd);
bool	set_visuals(t_vars *vars, t_data *data);
void	set_hooks(t_vars *vars);
void	free_visuals(t_vars *vars, t_data *data);
void	fill_map(char *file, t_map *map);
void	free_map(t_map *map);
void	draw_map(t_data *data, t_map *map);
int		calculate_color(float height, int start, int end);
void	set_map_rotation(t_map *map, float xy, float zy);
void	set_map_zoom(t_map *map, int zoom);
void	ft_mlx_put_pixel(t_data *data, t_point point);
int		get_sign(int num);
int		get_last_byte(int num);
int		print_error_and_return(char *str);
void	print_error_and_exit(char *str);

#endif
