/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:25:34 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 18:59:26 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define SCROLL_UP 4
# define SCROLL_DOWN 5

# include "fdf.h"
/*
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
*/
typedef struct s_env
{
	t_vars	*vars;
	t_data	*data;
	t_map	*map;
}	t_env;

void	set_hooks_bonus(t_vars *vars, t_data *img, t_map *map);
void	redraw_map(t_vars *vars, t_data *data, t_map *map);

#endif
