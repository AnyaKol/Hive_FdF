/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:25:34 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/20 13:16:11 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define SCROLL_UP 4
# define SCROLL_DOWN 5

# include "fdf.h"

typedef struct s_env
{
	t_vars	*vars;
	t_data	*data;
	t_map	*map;
}	t_env;

void	set_hooks_bonus(t_env *env);
void	redraw_map(t_vars *vars, t_data *data, t_map *map);

#endif
