/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:10:50 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/29 20:38:13 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_xpm(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (cub->data.wall_texture[i].pixels)
			free(cub->data.wall_texture[i].pixels);
		i++;
	}
	i = 0;
	while (i < cub->data.sprite_count)
	{
		if (cub->sprite && cub->sprite[i].texture.pixels)
			free(cub->sprite[i].texture.pixels);
		i++;
	}
}

void	free_all(t_cub *cub)
{
	if (cub)
	{
		if (cub->map)
			free_map(cub);
		if (cub->data.wall_distance)
			free(cub->data.wall_distance);
		if (cub->data.spr_ord)
			free(cub->data.spr_ord);
		if (cub->data.spr_idx)
			free(cub->data.spr_idx);
		if (cub->mlx)
			mlx_terminate(cub->mlx);
		free_xpm(cub);
		if (cub->sprite)
			free(cub->sprite);
		free(cub);
	}
}

void	free_map(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map[i])
	{
		free(cub->map[i]);
		i++;
	}
	free(cub->map);
}
