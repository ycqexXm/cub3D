/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:33:33 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/28 17:55:26 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_texture(char *line)
{
	int	direction;

	if (string_n_compare(line, "NO", 2) == 0 && is_space(line[2]))
		direction = NORTH;
	else if (string_n_compare(line, "EA", 2) == 0 && is_space(line[2]))
		direction = EAST;
	else if (string_n_compare(line, "SO", 2) == 0 && is_space(line[2]))
		direction = SOUTH;
	else if (string_n_compare(line, "WE", 2) == 0 && is_space(line[2]))
		direction = WEST;
	else if (string_n_compare(line, "DO", 2) == 0 && is_space(line[2]))
		direction = DOOR;
	else
		return (-1);
	line += 3;
	while (is_space(*line))
		line++;
	if (*line && *line != '\n')
		return (direction);
	else
		return (-1);
}

int	is_bg_color(char *line)
{
	int	id;
	int	i;

	if ((string_n_compare(line, "C", 1) == 0 && is_space(line[1])))
		id = 0;
	else if ((string_n_compare(line, "F", 1) == 0 && is_space(line[1])))
		id = 1;
	else
		return (-1);
	line += 2;
	while (is_space(*line))
		line++;
	i = -1;
	while (++i < 3)
	{
		while (is_digit(*line))
			line++;
		if (*line != ',' && i < 2)
			return (-1);
		line += (*line == ',' && i < 2);
	}
	while (is_space(*line))
		line++;
	return (id * (*line == '\n') - (*line != '\n'));
}

int	is_sprite(char *line)
{
	int	i;

	i = 0;
	if (!(string_n_compare(line, "S", 1) == 0 && is_space(line[1])))
		return (-1);
	line += 2;
	while (is_space(*line))
		line++;
	while (i < 3)
	{
		if (!is_float(line))
			return (-1);
		while (!isspace(*line))
			line++;
		while (isspace(*line))
			line++;
		i++;
	}
	if (*line && *line != '\n')
		return (1);
	return (-1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!line || line[i] == '\n')
		return (0);
	while (is_alnum(line[i]) || is_space(line[i]))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (i);
	return (0);
}

int	check_line_id(char *line)
{
	if (is_wall_texture(line) != -1)
		return (WALL);
	else if (is_bg_color(line) != -1)
		return (COLOR);
	else if (is_sprite(line) != -1)
		return (SPRITE);
	else if (is_map_line(line) != 0)
		return (MAP);
	else
	{
		while (is_space(*line))
			line++;
		if (*line == '\n')
			return (EMPTY_LINE);
	}
	return (0);
}
