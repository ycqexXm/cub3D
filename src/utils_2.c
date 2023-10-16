/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:48:20 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/28 18:14:43 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_space(int character)
{
	character = (unsigned char)character;
	if (character == '\t' || character == '\v'
		|| character == '\f' || character == '\r' || character == ' ')
		return (1);
	return (0);
}

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alnum(int c)
{
	if (is_alpha(c) || is_digit(c))
		return (1);
	return (0);
}

int	is_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_float(char *line)
{
	if (!is_digit(*line))
		return (0);
	while (is_digit(*line))
		line++;
	if (*line == '.')
	{
		line++;
		if (!is_digit(*line))
			return (-1);
		while (is_digit(*line))
			line++;
	}
	if (!isspace(*line))
		return (0);
	return (1);
}
