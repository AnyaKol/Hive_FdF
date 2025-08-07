/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:13:25 by akolupae          #+#    #+#             */
/*   Updated: 2025/04/15 11:16:49 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isdigit(int c)
{
	if ((unsigned char) c >= '0' && (unsigned char) c <= '9')
	{
		return (true);
	}
	return (false);
}
