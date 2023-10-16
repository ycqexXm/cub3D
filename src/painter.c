/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:09:47 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/28 18:12:49 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_color(t_cub *cub, t_texture wall, t_intxy coord, int *color)
{
	int	pixel;	

	pixel = (wall.texture.width * coord.y) + coord.x;
	if (cub->data.door == 2
		&& wall.texture.width / 2 < wall.coord.x && cub->data.door_side)
	{
		pixel -= ((wall.texture.width * wall.texture.bytes_per_pixel) / 2);
		*color = make_color(&cub->data.wall_texture[DOOR].pixels[pixel]);
	}
	else if (cub->data.door == 2
		&& wall.texture.width / 2 > wall.coord.x && !cub->data.door_side)
	{
		pixel += ((wall.texture.width * wall.texture.bytes_per_pixel) / 2);
		*color = make_color(&cub->data.wall_texture[DOOR].pixels[pixel]);
	}
	else
		*color = make_color(&wall.texture.pixels[pixel]);
}

void	draw_wall(t_cub *cub, t_texture wall, int x)
{
	int		y;
	int		color;
	t_intxy	coord;

	y = 0;
	coord.x = (int)wall.coord.x * wall.texture.bytes_per_pixel;
	while (y < WIN_H)
	{
		coord.y = (int)wall.coord.y * wall.texture.bytes_per_pixel;
		if (y <= wall.end && y >= wall.start)
		{
			wall_color(cub, wall, coord, &color);
			mlx_put_pixel(cub->image, x, y, color);
			wall.coord.y += wall.step;
		}
		else if (y < WIN_H / 2)
			mlx_put_pixel(cub->image, x, y, cub->data.ceiling_color);
		else
			mlx_put_pixel(cub->image, x, y, cub->data.floor_color);
		y++;
	}
}

void	draw_column(t_cub *cub, t_texture wall, int x, double wall_distance)
{
	double		height;

	height = (double)WIN_H / wall_distance;
	wall.step = (double)wall.texture.height / (double)height;
	wall.start = (WIN_H / 2) - (int)(height / 2);
	wall.end = (WIN_H / 2) + (int)(height / 2);
	if (wall.start < 0)
		wall.coord.y = (height / 2 - WIN_H / 2) * wall.step;
	else
		wall.coord.y = 0;
	draw_wall(cub, wall, x);
}
