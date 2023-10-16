/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:23:02 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/28 18:14:51 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_pixel(t_cub *cub, t_doublexy map, t_color *pixel)
{
	*pixel = 0xFFFFFF50;
	if (floor(map.x) < cub->data.width && floor(map.x) >= 0
		&& floor(map.y) < cub->data.height && floor(map.y) >= 0)
	{
		if (fabs(map.x - floor(map.x)) < 0.1
			|| fabs(map.y - floor(map.y)) < 0.1)
		{
			if (cub->map[(int)floor(map.y)][(int)floor(map.x)] != -1)
				*pixel = 0x000000FF;
		}
		else if (cub->map[(int)floor(map.y)][(int)floor(map.x)] != 0)
		{
			if (cub->map[(int)floor(map.y)][(int)floor(map.x)] == 1)
				*pixel = 0x404040FF;
			else if (cub->map[(int)floor(map.y)][(int)floor(map.x)] == 2)
				*pixel = 0x784710AA;
			else if (cub->map[(int)floor(map.y)][(int)floor(map.x)] == -2)
				*pixel = 0x784710FF;
		}
		else
			*pixel = cub->data.floor_color;
	}
}

void	draw_minimap(t_cub *cub, t_player player)
{
	double		x;
	double		y;
	double		w;
	t_doublexy	map;
	t_color		pixel;

	w = min(WIN_H, WIN_W) / 10.0;
	y = -1;
	while (++y < w * 2)
	{
		x = -1;
		while (++x < w * 2)
		{
			map.x = ((x - w) / w * 7.5 * (-player.dir.y)
					+ (y - w) / w * 7.5 * (-player.dir.x) + player.coord.x);
			map.y = ((x - w) / w * 7.5 * (+player.dir.x)
					+ (y - w) / w * 7.5 * (-player.dir.y) + player.coord.y);
			minimap_pixel(cub, map, &pixel);
			mlx_put_pixel(cub->image, x + w / 2, y + w / 2, pixel);
			if (x >= w - ((w / 20.0) * ((y - (w - w / 20.0)) / (w / 10.0)))
				&& x <= w + ((w / 20.0) * ((y - (w - w / 20.0)) / (w / 10.0)))
				&& y >= w - w / 20.0 && y <= w + w / 20.0)
				mlx_put_pixel(cub->image, x + w / 2, y + w / 2, 0xFF0000AA);
		}
	}
}
