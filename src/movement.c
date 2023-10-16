/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 19:05:07 by yorlians          #+#    #+#             */
/*   Updated: 2023/09/29 20:21:34 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	shift(mlx_t *mlx)
{
	return (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT));
}

void	egg(t_cub *cub, t_player *player, int **map)
{
	t_doublexy	spr_dir;
	int			i;
	double		r;

	i = -1;
	while (++i < cub->data.sprite_count && cub->data.s_move)
	{
		r = rand() % 100 / 500.0;
		spr_dir.x = r - 2 * r * (player->coord.x < cub->sprite[i].map_coord.x);
		spr_dir.y = r - 2 * r * (player->coord.y < cub->sprite[i].map_coord.y);
		if (map[(int)(cub->sprite[i].map_coord.y + spr_dir.y * 2)]
			[(int)cub->sprite[i].map_coord.x] < 1)
			cub->sprite[i].map_coord.y += spr_dir.y;
		if (map[(int)cub->sprite[i].map_coord.y]
			[(int)(cub->sprite[i].map_coord.x + spr_dir.x * 2)] < 1)
			cub->sprite[i].map_coord.x += spr_dir.x;
		if (floor(player->coord.x) == floor(cub->sprite[i].map_coord.x)
			&& floor(player->coord.y) == floor(cub->sprite[i].map_coord.y))
		{
			cub->data.pause = !cub->data.pause;
			cub->data.s_move = !cub->data.s_move;
			mlx_put_string(cub->mlx, EGG, WIN_W / 2 - 300, WIN_H / 4 * 3);
			break ;
		}
	}
}

void	apply_movement(t_cub *cub, int **map, t_player *player, t_doublexy dir)
{
	if (map[(int)(player->coord.y + dir.y)][(int)player->coord.x] < 1)
		player->coord.y += dir.y;
	if (map[(int)player->coord.y][(int)(player->coord.x + dir.x)] < 1)
		player->coord.x += dir.x;
	egg(cub, player, map);
}

void	move(t_cub *cub, int **map, t_player *player)
{
	t_doublexy	dir;

	dir.x = 0;
	dir.y = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
	{
		dir.x += player->dir.x * MOV_SPEED * (1 + shift(cub->mlx));
		dir.y += player->dir.y * MOV_SPEED * (1 + shift(cub->mlx));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
	{
		dir.x += -player->dir.x * MOV_SPEED * (1 + shift(cub->mlx));
		dir.y += -player->dir.y * MOV_SPEED * (1 + shift(cub->mlx));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		dir.x += -player->dir.y * MOV_SPEED * (1 + shift(cub->mlx));
		dir.y += player->dir.x * MOV_SPEED * (1 + shift(cub->mlx));
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		dir.x += player->dir.y * MOV_SPEED * (1 + shift(cub->mlx));
		dir.y += -player->dir.x * MOV_SPEED * (1 + shift(cub->mlx));
	}
	apply_movement(cub, map, player, dir);
}
