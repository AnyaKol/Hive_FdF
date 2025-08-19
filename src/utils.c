/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 11:52:31 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_put_pixel(t_data *data, t_point point)
{
	char	*dst;

	if (point.x >= 0 && point.x < WIDTH && point.y >= 0 && point.y < HEIGHT)
	{
		dst = data->addr + (point.y * data->line_length + point.x
				* (data->bits_per_pixel / 8));
		*(unsigned int *) dst = point.color;
	}
}

int	sign(int num)
{
	return ((num > 0) - (num < 0));
}

int	get_last_byte(int num)
{
	return (num & 0x0000FF);
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
