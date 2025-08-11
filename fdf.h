/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:25:34 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/11 16:38:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 600
# define HEIGHT 600
# define STDOUT 1
# define STDERR 2

# include "libft.h"
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"
# include "lodepng/lodepng.h"
# include "KHR/khrplatform.h"
# include "glad/glad.h"
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_map
{
	int	cols;
	int	rows;
	int	**values;
}	t_map;

void	check_args(int argc, char **argv, t_map *map);
void	fill_map(char *file, t_map *map);
void	free_map(t_map *map);
void	clean_up(char *line, int fd);

#endif
