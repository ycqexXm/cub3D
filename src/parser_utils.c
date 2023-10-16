/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:24:44 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/30 14:49:31 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_wall_texture(t_cub *cub, char *line, int *textures, int fd)
{
	xpm_t	*xpm;
	char	*filename;
	char	*original;
	int		direction;

	original = line;
	direction = is_wall_texture(line);
	if (cub->data.thereistexture[direction])
		error_message(TEXT_DUP_ERR, cub, fd);
	cub->data.thereistexture[direction] = 1;
	line += 3;
	while (is_space(*line))
		line++;
	*find_char(line, '\n') = '\0';
	filename = str_dup(line);
	xpm = mlx_load_xpm42(filename);
	free(filename);
	if (!xpm)
	{
		free(original);
		error_message(ERR_L_XPM, cub, fd);
	}
	cub->data.wall_texture[direction] = xpm->texture;
	(*textures)++;
	free(xpm);
}

void	get_data_color(t_cub *cub, char *line, int fd)
{
	t_color	*color;
	int		channel[3];
	int		i;

	i = 0;
	color = NULL;
	if (is_bg_color(line) == 0)
		color = &cub->data.ceiling_color;
	else if (is_bg_color(line) == 1)
		color = &cub->data.floor_color;
	if (!color || *color)
		error_message(DUP_ERR, cub, fd);
	line += 2;
	while (is_space(*line))
		line++;
	while (line && i < 3)
	{
		channel[i++] = atoi_cub(line);
		if (channel[i - 1] > 255)
			error_message(COLOR_RANGE_ERR, cub, fd);
		line = find_char(line, ',');
		if (line)
			line++;
	}
	*color = get_rgba(channel[0], channel[1], channel[2], 0xFF);
}

double	get_next_num(char **line)
{
	int		decimals;
	int		i;
	double	number;

	decimals = 0;
	i = 0;
	number = 0;
	while (is_space((*line)[i]))
		i++;
	if (is_digit((*line)[i]))
		number = atoi_cub((*line) + i);
	while (is_digit((*line)[i]))
		i++;
	if ((*line)[i] == ',' || (*line)[i] == '.')
	{
		i++;
		while (is_digit((*line)[i++]))
			decimals++;
		number += ((double)atoi_cub((*line) + i - decimals)
				/ powf(10.0, (double)decimals));
	}
	while (is_space((*line)[i]))
		i++;
	(*line) += i;
	return (number);
}

void	get_sprite(t_cub *cub, char *line, t_sprite *sprite, int fd)
{
	char	*original;
	char	*filename;
	xpm_t	*xpm;

	original = line;
	line++;
	sprite->map_coord.x = (double)get_next_num(&line);
	sprite->map_coord.y = (double)get_next_num(&line);
	sprite->scale = (double)get_next_num(&line);
	*find_char(line, '\n') = '\0';
	filename = str_dup(line);
	xpm = mlx_load_xpm42(filename);
	free(filename);
	if (!xpm)
	{
		free(original);
		error_message(ERR_L_XPM, cub, fd);
	}
	sprite->texture = xpm->texture;
	free(xpm);
}

void	assign_start(t_cub *cub, char c, int x, int y)
{
	cub->player.coord.x = y + 0.5;
	cub->player.coord.y = x + 0.5;
	if (c == 'N')
	{
		cub->player.plane.x = 0.7;
		cub->player.dir.y = -1;
	}
	else if (c == 'S')
	{
		cub->player.plane.x = -0.7;
		cub->player.dir.y = 1;
	}
	else if (c == 'W')
	{
		cub->player.plane.y = -0.7;
		cub->player.dir.x = -1;
	}
	else if (c == 'E')
	{
		cub->player.plane.y = 0.7;
		cub->player.dir.x = 1;
	}
	cub->data.thereisplayer = 1;
}
