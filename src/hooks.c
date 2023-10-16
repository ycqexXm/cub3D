/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:30:11 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/29 20:20:31 by bluzi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_hook(t_cub *cub, mlx_key_data_t keydata)
{
	t_intxy		coord;
	t_player	player;
	int			**map;

	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		map = cub->map;
		player = cub->player;
		coord.x = (int)floor(player.coord.x + player.dir.x);
		coord.y = (int)floor(player.coord.y + player.dir.y);
		if (abs(map[coord.y][coord.x]) == 2
			&& !(coord.x == (int)floor(player.coord.x)
			&& coord.y == (int)floor(player.coord.y)))
			map[coord.y][coord.x] *= -1;
	}
}

void	pause_hook(t_cub *cub, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		cub->data.pause = !cub->data.pause;
		if (cub->data.pause)
		{
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
			mlx_put_string(cub->mlx, "PAUSE", WIN_W / 2, WIN_H / 2);
		}
		else
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	}
	if (keydata.key == MLX_KEY_LEFT_CONTROL && keydata.action == MLX_PRESS)
		cub->data.s_move = !cub->data.s_move;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub		*cub;

	cub = param;
	door_hook(cub, keydata);
	pause_hook(cub, keydata);
}

void	rotate(t_cub *cub, t_player *player)
{
	t_intxy			pos;
	double			speed;
	double			old_dir_x;
	double			old_plane_x;

	mlx_get_mouse_pos(cub->mlx, &pos.x, &pos.y);
	speed = (double)((pos.x - WIN_W / 2) * ROT_SPEED / 30.0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		speed = ROT_SPEED + ROT_SPEED * shift(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		speed = -ROT_SPEED - ROT_SPEED * shift(cub->mlx);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(speed) - player->dir.y * sin(speed);
	player->dir.y = old_dir_x * sin(speed) + player->dir.y * cos(speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x
		* cos(speed) - player->plane.y * sin(speed);
	player->plane.y = old_plane_x * sin(speed) + player->plane.y * cos(speed);
	mlx_set_mouse_pos(cub->mlx, WIN_W / 2, WIN_H / 2);
}

void	hook(void *param)
{
	t_cub	*cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (!cub->data.pause)
	{
		move(cub, cub->map, &cub->player);
		rotate(cub, &cub->player);
		if (!cub->data.pause)
			redraw_image(cub);
	}
}
