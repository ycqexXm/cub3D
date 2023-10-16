/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:16:29 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/28 13:42:59 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	door_hit(t_cub *cub, t_ray *ray)
{
	if (cub->data.side == 0
		&& ray->length.x - (ray->delta.x / 2.0) < ray->length.y)
	{
		ray->length.x += ray->delta.x / 2.0;
		cub->data.door = 1;
		return (1);
	}
	else if (cub->data.side == 1
		&& ray->length.y - (ray->delta.y / 2.0) < ray->length.x)
	{
		ray->length.y += ray->delta.y / 2.0;
		cub->data.door = 1;
		return (1);
	}
	return (0);
}

int	surface_hit(t_cub *cub, t_ray *ray)
{
	if (cub->map[ray->coord.y][ray->coord.x] == 1)
	{		
		if ((cub->map[ray->coord.y - (cub->data.side * ray->step.y)] \
			[ray->coord.x - (!cub->data.side * ray->step.x)]) == -2)
		{
			if ((cub->map[ray->coord.y - (cub->data.side * ray->step.y) * 2] \
				[ray->coord.x - (!cub->data.side * ray->step.x) * 2]) == 1)
				cub->data.door = 2;
		}
		return (1);
	}
	else if (cub->map[ray->coord.y][ray->coord.x] == 2)
		return (door_hit(cub, ray));
	return (0);
}

void	dda(t_cub *cub, t_ray *ray, double *wall_distance)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->length.x += ray->delta.x;
			ray->coord.x += ray->step.x;
			cub->data.side = 0;
		}
		else
		{
			ray->length.y += ray->delta.y;
			ray->coord.y += ray->step.y;
			cub->data.side = 1;
		}
		cub->data.door = 0;
		hit = surface_hit(cub, ray);
	}
	if (cub->data.side == 0)
		*wall_distance = ray->length.x - ray->delta.x;
	else
		*wall_distance = ray->length.y - ray->delta.y;
}

void	calculate_ray_deltas(t_cub *cub, t_ray *ray)
{
	if (ray->dir.x)
		ray->delta.x = fabs(1.0 / ray->dir.x);
	else
		ray->delta.x = INFINITY;
	if (ray->dir.y)
		ray->delta.y = fabs(1.0 / ray->dir.y);
	else
		ray->delta.y = INFINITY;
	ray->step.x = 1 - (2 * (ray->dir.x < 0));
	ray->step.y = 1 - (2 * (ray->dir.y < 0));
	if (ray->dir.x < 0)
		ray->length.x = (cub->player.coord.x - (float)ray->coord.x)
			* ray->delta.x;
	else
		ray->length.x = ((float)ray->coord.x - cub->player.coord.x + 1.0)
			* ray->delta.x;
	if (ray->dir.y < 0)
		ray->length.y = (cub->player.coord.y - (float)ray->coord.y)
			* ray->delta.y;
	else
		ray->length.y = ((float)ray->coord.y - cub->player.coord.y + 1.0)
			* ray->delta.y;
}

void	ray_loop(t_cub *cub)
{
	double		camera_x;
	int			x;
	t_ray		ray;
	t_player	player;

	x = 0;
	player = cub->player;
	while (x < WIN_W)
	{
		camera_x = (2.0 * (double)x / (double)WIN_W) - 1.0;
		ray.dir.x = player.dir.x + (player.plane.x * camera_x);
		ray.dir.y = player.dir.y + (player.plane.y * camera_x);
		ray.coord.x = (int)player.coord.x;
		ray.coord.y = (int)player.coord.y;
		calculate_ray_deltas(cub, &ray);
		dda(cub, &ray, &cub->data.wall_distance[x]);
		texture_data(cub, &cub->data.wall, ray, cub->data.wall_distance[x]);
		draw_column(cub, cub->data.wall, x, cub->data.wall_distance[x]);
		x++;
	}
	draw_sprites(cub, player, cub->sprite);
	draw_minimap(cub, player);
}
