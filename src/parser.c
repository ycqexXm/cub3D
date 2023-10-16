/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 02:34:13 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/30 14:44:50 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_size(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message(OPEN_FAIL, cub, fd);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || !check_line_id(line))
			break ;
		if (check_line_id(line) == 3)
			cub->data.sprite_count++;
		if (check_line_id(line) == 4)
			cub->data.height++;
		if (check_line_id(line) == 4 && cub->data.width < is_map_line(line))
			cub->data.width = is_map_line(line);
		free(line);
	}
	close(fd);
	if ((line && !check_line_id(line)) || !cub->data.height)
	{
		free(line);
		error_message(PARS_ERR, cub, -1);
	}
}

void	get_textures(t_cub *cub, int fd, char **line)
{
	int		textures;
	int		colours;
	int		sprites;

	textures = 0;
	colours = 0;
	sprites = 0;
	while (1)
	{
		*line = get_next_line(fd);
		if (!*line || check_line_id(*line) == 4)
			break ;
		if (check_line_id(*line) == 1)
			get_wall_texture(cub, *line, &textures, fd);
		else if (check_line_id(*line) == 2)
		{
			get_data_color(cub, *line, fd);
			colours++;
		}
		else if (check_line_id(*line) == 3)
			get_sprite(cub, *line, &cub->sprite[sprites++], fd);
		free(*line);
	}
	if (!texture_check(cub, textures) || colours != 2)
		error_message(TEXTURE_NUM_ERR, cub, fd);
}

void	get_map_square(t_cub *cub, char c, t_intxy coord, int fd)
{
	if (is_space(c))
		cub->map[coord.x][coord.y] = -1;
	else if (c == '0')
		cub->map[coord.x][coord.y] = 0;
	else if (c == '1')
		cub->map[coord.x][coord.y] = 1;
	else if (c == '2')
	{
		if (!cub->data.thereistexture[DOOR])
			error_message(MISS_DOOR, cub, fd);
		cub->map[coord.x][coord.y] = 2;
	}
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (cub->data.start)
			error_message(START_POS_ERR, cub, fd);
		else
			cub->data.start = 1;
		assign_start(cub, c, coord.x, coord.y);
		cub->map[coord.x][coord.y] = 0;
	}
	else
		error_message(UNEX_PARAM, cub, fd);
}

void	get_map(t_cub *cub, int fd, char *line)
{
	t_intxy	coord;

	cub->map = calloc_cub((cub->data.height + 1), sizeof(int *));
	coord.x = 0;
	while (coord.x < cub->data.height)
	{
		coord.y = 0;
		cub->map[coord.x] = calloc_cub(cub->data.width, sizeof(int));
		while (coord.y < cub->data.width)
		{
			get_map_square(cub, line[coord.y], coord, fd);
			coord.y++;
			if (line[coord.y] == '\0' || line[coord.y] == '\n')
				break ;
		}
		while (coord.y < cub->data.width)
			cub->map[coord.x][coord.y++] = -1;
		if (line)
			free(line);
		line = get_next_line(fd);
		coord.x++;
	}
	cub->map[coord.x] = NULL;
}

void	parser(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;

	get_size(cub, filename);
	if (cub->data.sprite_count)
	{
		cub->sprite = calloc_cub(cub->data.sprite_count, sizeof(t_sprite));
		if (!cub->sprite)
			error_message(FAIL_ALLOC, cub, -1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message(OPEN_FAIL, cub, fd);
	get_textures(cub, fd, &line);
	get_map(cub, fd, line);
	close(fd);
	map_check(cub, cub->map);
}
