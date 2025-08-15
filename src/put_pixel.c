/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/15 19:41:44 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	calculate_color(float height);
static int	get_color(t_level level);
static int	get_color_percent(int start, int end, float height);
static int	get_last_byte(int num);


void	ft_mlx_put_pixel(t_data *data, t_point point)
{
	char	*dst;

	if (point.x >= 0 && point.x < WIDTH && point.y >= 0 && point.y < HEIGHT)
	{
		dst = data->addr + (point.y * data->line_length + point.x
			* (data->bits_per_pixel / 8));
		*(unsigned int *) dst = calculate_color(point.height);
	}
}

static int	calculate_color(float height)
{
	int	start;
	int	end;
	int	color;

	if (height == 0)
		return (get_color(MIDDLE));
	start = get_color(MIDDLE);
	if (height > 0)
		end = get_color(HIGH);
	else
	{
		end = get_color(LOW);
		height = -height;
	}
	color = 0x000000;
	color |= get_color_percent(start >> 16, end >> 16, height) << 16;
	color |= get_color_percent(start >> 8, end >> 8, height) << 8;
	color |= get_color_percent(start, end, height);
	return (color);
}

static int	get_color(t_level level)
{
	const int	colors[3] = {
		0xFF0000,
		0X00FF00,
		0X0000FF
	};
	return (colors[level]);
}

static int	get_color_percent(int start, int end, float height)
{
	int	color;

	start = get_last_byte(start);
	end = get_last_byte(end);
	color = start + (end - start) * height;
	//color = get_last_byte(color);
	return (color);
}

static int	get_last_byte(int num)
{
	return (num & 0x0000FF);
}
