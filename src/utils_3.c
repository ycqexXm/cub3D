/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:50:33 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/30 13:56:28 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*calloc_cub(size_t count, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(count * size);
	if (str == NULL)
		return (0);
	if ((count > 65535 || size > 65535) && (size_t)-1 / count < size)
		return (NULL);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

void	error_message(char *message, t_cub *cub, int fd)
{
	put_str("\033[1;91mError :\n\033[0m", STDOUT_FILENO);
	put_str(message, STDOUT_FILENO);
	put_str("\n", STDOUT_FILENO);
	if (fd >= 0)
		close(fd);
	if (cub)
		free_all(cub);
	exit(EXIT_FAILURE);
}

void	put_str(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		put_char(s[i], fd);
		i++;
	}
}

void	put_char(char c, int fd)
{
	write (fd, &c, 1);
}

int	min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	else
		return (n2);
}
