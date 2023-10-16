/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:19:03 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/28 17:56:02 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	string_n_compare(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}

char	*find_char(char *string, char c)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (string + i);
		i++;
	}
	return (NULL);
}

char	*str_dup(const char *s1)
{
	char	*s1c;
	size_t	len;
	size_t	i;

	len = str_len(s1);
	s1c = malloc((len + 1) * sizeof(char));
	i = 0;
	if (s1c == 0)
		return (0);
	while (i < len)
	{
		s1c[i] = s1[i];
		i++;
	}
	s1c[i] = '\0';
	return (s1c);
}

int	str_len(const char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}

int	atoi_cub(char *str)
{
	int		sign;
	int		result;
	int		i;

	str = (char *)str;
	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (is_digit(str[i]))
	{
		if (result * sign > 2147483647 || result * sign < -2147483647)
			return (1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
