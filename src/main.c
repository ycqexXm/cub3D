/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:10:24 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/30 15:11:16 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_data_arrays(t_cub *cub)
{
	cub->data.wall_distance = calloc_cub(WIN_W, sizeof(double));
	if (!cub->data.wall_distance)
		error_message(FAIL_ALLOC, cub, -1);
	cub->data.spr_ord = calloc_cub(cub->data.sprite_count, sizeof(double));
	if (!cub->data.spr_ord && cub->data.sprite_count)
		error_message(FAIL_ALLOC, cub, -1);
	cub->data.spr_idx = calloc_cub(cub->data.sprite_count, sizeof(int));
	if (!cub->data.spr_idx && cub->data.sprite_count)
		error_message(FAIL_ALLOC, cub, -1);
}

void	redraw_image(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->image);
	cub->image = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	ray_loop(cub);
	mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
		error_message(ARG_ERROR, NULL, -1);
	cub = calloc_cub(1, sizeof(t_cub));
	if (!cub)
		error_message(FAIL_ALLOC, cub, -1);
	ends_with_cub(cub, argv[1]);
	parser(cub, argv[1]);
	alloc_data_arrays(cub);
	cub->mlx = mlx_init(WIN_W, WIN_H, "Cub3D", 0);
	cub->image = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, WIN_W / 2, WIN_H / 2);
	ray_loop(cub);
	mlx_image_to_window(cub->mlx, cub->image, 0, 0);
	mlx_key_hook(cub->mlx, &key_hook, cub);
	mlx_loop_hook(cub->mlx, &hook, cub);
	mlx_loop(cub->mlx);
	free_all(cub);
	return (EXIT_SUCCESS);
}
