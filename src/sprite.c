/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:25:10 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/28 18:12:32 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_size(t_player pl, t_sprite *spr)
{
	double		inv_det;

	spr->coord.x = spr->map_coord.x - pl.coord.x;
	spr->coord.y = spr->map_coord.y - pl.coord.y;
	inv_det = 1.0 / (pl.plane.x * pl.dir.y - pl.dir.x * pl.plane.y);
	spr->transform.x = inv_det
		* (pl.dir.y * spr->coord.x - pl.dir.x * spr->coord.y);
	spr->transform.y = inv_det
		* (-pl.plane.y * spr->coord.x + pl.plane.x * spr->coord.y);
	spr->coord.x = ((double)WIN_W / 2.0)
		* (1.0 + spr->transform.x / spr->transform.y);
	spr->height = abs((int)((double)WIN_H / spr->transform.y)) / spr->scale;
	spr->translate = (((double)WIN_H - (double)((double)WIN_H / spr->scale))
			/ 2.0) / spr->transform.y;
	spr->step.y = (double)spr->texture.height / spr->height;
	spr->start.y = WIN_H / 2 - ((int)spr->height / 2) + spr->translate;
	spr->end.y = WIN_H / 2 + ((int)spr->height / 2) + spr->translate;
	spr->width = abs((int)((double)WIN_H / spr->transform.y)) / spr->scale;
	spr->step.x = (double)spr->texture.width / spr->width;
	spr->start.x = spr->coord.x - (spr->width / 2);
	spr->end.x = spr->coord.x + (spr->width / 2);
	spr->coord.y = fabs((double)spr->start.y) * spr->step.y
		* (spr->start.y < 0);
	spr->coord.x = fabs((double)spr->start.x) * spr->step.x
		* (spr->start.x < 0);
}

void	draw_sprite_column(t_cub *cub, t_sprite sprite, int x)
{
	int		y;
	int		color;
	t_intxy	coord;

	sprite.coord.y = fabs((double)sprite.start.y) * sprite.step.y
		* (sprite.start.y < 0);
	y = sprite.start.y * (sprite.start.y >= 0);
	while (y < sprite.end.y && y < WIN_H
		&& sprite.transform.y < cub->data.wall_distance[x])
	{
		coord.x = floor(sprite.coord.x) * sprite.texture.bytes_per_pixel;
		coord.y = floor(sprite.coord.y) * sprite.texture.bytes_per_pixel;
		if (coord.y / sprite.texture.bytes_per_pixel
			< (int)sprite.texture.height && coord.x
			/ sprite.texture.bytes_per_pixel < (int)sprite.texture.width)
		{
			color = make_color(&sprite.texture.pixels
				[(sprite.texture.width * coord.y + coord.x)]);
			if (get_a(color) != 0)
				mlx_put_pixel(cub->image, x, y, color);
		}
		sprite.coord.y += sprite.step.y;
		y++;
	}
}

void	order_sprites(t_cub *cub)
{
	int		i;
	int		j;
	double	temp;
	int		temp_idx;

	i = -1;
	while (++i < cub->data.sprite_count)
	{
		j = i;
		while (++j < cub->data.sprite_count)
		{
			if (cub->data.spr_ord[i] > cub->data.spr_ord[j])
			{
				temp = cub->data.spr_ord[i];
				temp_idx = cub->data.spr_idx[i];
				cub->data.spr_ord[i] = cub->data.spr_ord[j];
				cub->data.spr_idx[i] = cub->data.spr_idx[j];
				cub->data.spr_ord[j] = temp;
				cub->data.spr_idx[j] = temp_idx;
			}
		}
	}
}

void	draw_sprites(t_cub *cub, t_player player, t_sprite *sprite)
{
	int		n;
	int		x;

	n = -1;
	while (++n < cub->data.sprite_count)
	{
		sprite_size(player, &(sprite[n]));
		cub->data.spr_ord[n] = sprite[n].translate;
		cub->data.spr_idx[n] = n;
	}
	order_sprites(cub);
	n = -1;
	while (++n < cub->data.sprite_count)
	{
		x = sprite[(int)cub->data.spr_idx[n]].start.x
			* (sprite[(int)cub->data.spr_idx[n]].start.x >= 0);
		while (x < sprite[(int)cub->data.spr_idx[n]].end.x && x < WIN_W
			&& sprite[(int)cub->data.spr_idx[n]].transform.y > 0)
		{
			draw_sprite_column(cub, sprite[(int)cub->data.spr_idx[n]], x);
			sprite[(int)cub->data.spr_idx[n]].coord.x
				+= sprite[(int)cub->data.spr_idx[n]].step.x;
			x++;
		}
	}
}
