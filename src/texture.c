/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:40:58 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/26 19:22:20 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_texture(t_cub *cub, t_texture *wall, t_ray ray)
{
	if (cub->data.door == 1)
		wall->texture = cub->data.wall_texture[DOOR];
	else if (cub->data.side == 0 && ray.dir.x > 0)
		wall->texture = cub->data.wall_texture[WEST];
	else if (cub->data.side == 0 && ray.dir.x < 0)
		wall->texture = cub->data.wall_texture[EAST];
	else if (cub->data.side == 1 && ray.dir.y > 0)
		wall->texture = cub->data.wall_texture[NORTH];
	else if (cub->data.side == 1 && ray.dir.y < 0)
		wall->texture = cub->data.wall_texture[SOUTH];
	if (cub->data.side == 0 && ray.dir.x > 0)
		cub->data.door_side = 1;
	else if (cub->data.side == 0 && ray.dir.x < 0)
		cub->data.door_side = 0;
	else if (cub->data.side == 1 && ray.dir.y > 0)
		cub->data.door_side = 0;
	else if (cub->data.side == 1 && ray.dir.y < 0)
		cub->data.door_side = 1;
}

void	texture_data(t_cub *cub, t_texture *wall, t_ray ray, double wall_dst)
{
	select_texture(cub, wall, ray);
	if (cub->data.side == 0)
	{
		wall->coord.x = (wall_dst * ray.dir.y) + cub->player.coord.y;
		wall->coord.x -= (int)(wall->coord.x);
		wall->coord.x *= (double)wall->texture.width;
		if (ray.step.x <= 0)
			wall->coord.x = wall->texture.width - wall->coord.x - 1;
	}
	else
	{
		wall->coord.x = (wall_dst * ray.dir.x) + cub->player.coord.x;
		wall->coord.x -= (int)(wall->coord.x);
		wall->coord.x *= (double)wall->texture.width;
		if (ray.step.y >= 0)
			wall->coord.x = wall->texture.width - wall->coord.x - 1;
	}
}
