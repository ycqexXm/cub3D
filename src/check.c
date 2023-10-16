/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:42:48 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/30 14:35:20 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_check(t_cub *cub, int textures)
{
	if (textures == 4 && !cub->data.thereistexture[DOOR])
		return (1);
	else if (textures == 5 && cub->data.thereistexture[DOOR])
		return (1);
	return (0);
}

void	ends_with_cub(t_cub *cub, char *path)
{
	char	*extension;

	extension = find_char(path, '.');
	if (!(extension != 0 && string_n_compare(extension, ".cub", 5) == 0))
		error_message(EXT_ERROR, cub, -1);
}

int	valid_surroundings(t_cub *cub, int **map, int x, int y)
{
	int	i;

	i = -1;
	if (x <= 0 || x >= cub->data.height - 1)
		return (0);
	if (y <= 0 || y >= cub->data.width - 1)
		return (0);
	while (i < 2)
	{
		if (map[x + i][y - 1] == -1)
			return (0);
		if (map[x + i][y] == -1)
			return (0);
		if (map[x + i][y + 1] == -1)
			return (0);
		i++;
	}
	return (1);
}

int	valid_door(int **map, int x, int y)
{
	if (map[x - 1][y] == 2 || map[x + 1][y] == 2)
		return (0);
	if (map[x][y - 1] == 2 || map[x][y + 1] == 2)
		return (0);
	if (map[x - 1][y] == 1 && map[x + 1][y] == 1)
		return (1);
	if (map[x][y - 1] == 1 && map[x][y + 1] == 1)
		return (1);
	return (0);
}

void	map_check(t_cub *cub, int **map)
{
	int	x;
	int	y;

	if (!cub->data.thereisplayer)
		error_message(PARS_ERR, cub, -1);
	x = 0;
	while (x < cub->data.height)
	{
		y = 0;
		while (y < cub->data.width)
		{
			if ((map[x][y] == 0 || map[x][y] == 2)
				&& !valid_surroundings(cub, map, x, y))
				error_message(WALLS_ERR, cub, -1);
			else if (map[x][y] == 2 && !valid_door(map, x, y))
				error_message(DOOR_ERR, cub, -1);
			y++;
		}
		x++;
	}
}
