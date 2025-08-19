/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:47:28 by akolupae          #+#    #+#             */
/*   Updated: 2025/08/19 12:00:38 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_color_level(t_level level);
static int	get_color_percent(int start, int end, float height);

int	calculate_color(float height, int start, int end)
{
	int	color;

	if (start == NO_COLOR)
		start = get_color_level(MIDDLE);
	if (height > 0 && end == NO_COLOR)
		end = get_color_level(HIGH);
	else if (height < 0)
	{
		if (end == NO_COLOR)
			end = get_color_level(LOW);
		height = -height;
	}
	color = 0x000000;
	color |= get_color_percent(start >> 16, end >> 16, height) << 16;
	color |= get_color_percent(start >> 8, end >> 8, height) << 8;
	color |= get_color_percent(start, end, height);
	return (color);
}

static int	get_color_level(t_level level)
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
	return (color);
}

int	skip_color(char *line)
{
	int	i;

	i = 0;
	if (!ft_strncmp(&line[i], ",0x", 3))
	{
		i += 3;
		while (ft_strchr(BASE_HEX, line[i]) || ft_strchr(BASE_HEX_LOW, line[i]))
			i++;
	}
	return (i);
}

int	get_color_from_arg(char *line)
{
	int	color;

	color = ft_atoi_base(line, BASE_HEX);
	if (color == 0)
		color = ft_atoi_base(line, BASE_HEX_LOW);
	return (color);
}
