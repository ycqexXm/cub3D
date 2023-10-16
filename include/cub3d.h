/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 18:11:15 by bluzi             #+#    #+#             */
/*   Updated: 2023/09/30 15:05:47 by yorlians         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/******************************************************************************
*								  Libraries									  *
******************************************************************************/

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <ctype.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../src/get_next_line/get_next_line.h"

/******************************************************************************
*								  Macros									  *
******************************************************************************/

# define NORTH					0
# define EAST					1
# define SOUTH					2
# define WEST					3
# define DOOR					4

# define WALL					1
# define COLOR					2
# define SPRITE					3
# define MAP					4
# define EMPTY_LINE				5

# define WIN_W					1920
# define WIN_H					1080

# define MOV_SPEED				0.075
# define ROT_SPEED				0.0174533

# define ARG_ERROR				"\033[1;91mWrong number of arguments\033[0m"
# define FAIL_ALLOC				"\033[1;91mAllocation failed\033[0m"
# define EXT_ERROR				"\033[1;91mExtension is not .cub\033[0m"
# define UNEX_PARAM				"\033[1;91mUnexpected parameter\033[0m"
# define WALLS_ERR				"\033[1;91mThere is a wall missing\033[0m"
# define DOOR_ERR				"\033[1;91mDoors can be only placed in between\
 two walls\033[0m"
# define ERR_L_XPM				"\033[1;91mUnable to load xpm42\033[0m"
# define COLOR_RANGE_ERR		"\033[1;91mColor outside of acceptable\
 range [0,255]\033[0m"
# define OPEN_FAIL				"\033[1;91mUnable to open\033[0m"
# define TEXTURE_NUM_ERR		"\033[1;91mWrong number of textures and/or\
 colors\033[0m"
# define PARS_ERR				"\033[1;91mParsing error\033[0m"
# define DUP_ERR				"\033[1;91mColor assignment error\033[0m"
# define TEXT_DUP_ERR			"\033[1;91mThere are duplicates\
 among textures\033[0m"
# define START_POS_ERR			"\033[1;91mThere can be only one starting\
 position\033[0m"
# define MISS_DOOR				"\033[1;91mThe texture of the\
 door is missing\033[0m"

# define EGG					"I S   I T   A N I M A T E D   E N O U G H ! ?"

/******************************************************************************
*								  Structures								  *
******************************************************************************/

typedef struct s_doublexy
{
	double	x;
	double	y;
}	t_doublexy;

typedef struct s_intxy
{
	int	x;
	int	y;
}	t_intxy;

typedef int32_t	t_color;

typedef struct s_texture
{
	mlx_texture_t	texture;
	t_doublexy		coord;
	double			step;
	int				start;
	int				end;
}	t_texture;

typedef struct s_data
{
	double			*wall_distance;
	double			*spr_ord;
	int				*spr_idx;
	int				width;
	int				height;
	int				pause;
	int				s_move;
	int				start;
	int				side;
	int				door;
	int				door_side;
	int				sprite_count;
	int				thereisplayer;
	int				thereistexture[5];
	t_texture		wall;
	mlx_texture_t	wall_texture[5];
	t_color			floor_color;
	t_color			ceiling_color;
}	t_data;

typedef struct s_ray
{
	t_doublexy	dir;
	t_intxy		coord;
	t_intxy		step;
	t_doublexy	delta;
	t_doublexy	length;
}	t_ray;

typedef struct s_player
{
	t_doublexy	coord;
	t_doublexy	plane;
	t_doublexy	dir;
}	t_player;

typedef struct s_sprite
{
	t_doublexy		map_coord;
	mlx_texture_t	texture;
	t_doublexy		transform;
	t_doublexy		coord;
	t_doublexy		step;
	t_intxy			start;
	t_intxy			end;
	double			width;
	double			height;
	double			scale;
	double			translate;
}	t_sprite;

typedef struct s_cub
{
	t_data		data;
	t_sprite	*sprite;
	int			**map;
	t_player	player;
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_cub;

/******************************************************************************
*								  Functions									  *
******************************************************************************/

//			check
void		ends_with_cub(t_cub *cub, char *path);
int			valid_surroundings(t_cub *cub, int **map, int x, int y);
int			valid_door(int **map, int x, int y);
void		map_check(t_cub *cub, int **map);
int			texture_check(t_cub *cub, int textures);

//			color utils
int			get_rgba(int r, int g, int b, int a);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_a(int rgba);

//			color
uint32_t	make_color(uint8_t *pixel);

//			free all
void		free_all(t_cub *cub);
void		free_map(t_cub *cub);
void		free_xpm(t_cub *cub);

//			hooks
void		door_hook(t_cub *cub, mlx_key_data_t keydata);
void		pause_hook(t_cub *cub, mlx_key_data_t keydata);
void		key_hook(mlx_key_data_t keydata, void *param);
void		rotate(t_cub *cub, t_player *player);
void		hook(void *param);

//			id_check
int			is_wall_texture(char *line);
int			is_bg_color(char *line);
int			is_sprite(char *line);
int			is_map_line(char *line);
int			check_line_id(char *line);

//			main
void		alloc_data_arrays(t_cub *cub);
void		redraw_image(t_cub *cub);

//			minimap
void		minimap_pixel(t_cub *cub, t_doublexy map, t_color *pixel);
void		draw_minimap(t_cub *cub, t_player player);

//			movement
int			shift(mlx_t *mlx);
void		egg(t_cub *cub, t_player *player, int **map);
void		apply_movement(t_cub *cub, int **map, t_player *player, \
			t_doublexy dir);
void		move(t_cub *cub, int **map, t_player *player);

//			painter
void		wall_color(t_cub *cub, t_texture wall, t_intxy coord, int *color);
void		draw_wall(t_cub *cub, t_texture wall, int x);
void		draw_column(t_cub *cub,
				t_texture wall, int x, double wall_distance);

//			parser utils
void		get_wall_texture(t_cub *cub, char *line, int *textures, int fd);
void		get_data_color(t_cub *cub, char *line, int fd);
double		get_next_num(char **line);
void		get_sprite(t_cub *cub, char *line, t_sprite *sprite, int fd);
void		assign_start(t_cub *cub, char c, int x, int y);

//			parser
void		get_size(t_cub *cub, char *filename);
void		get_textures(t_cub *cub, int fd, char **line);
void		get_map_square(t_cub *cub, char c, t_intxy coord, int fd);
void		get_map(t_cub *cub, int fd, char *line);
void		parser(t_cub *cub, char *filename);

//			ray cast
int			door_hit(t_cub *cub, t_ray *ray);
int			surface_hit(t_cub *cub, t_ray *ray);
void		dda(t_cub *cub, t_ray *ray, double *wall_distance);
void		calculate_ray_deltas(t_cub *cub, t_ray *ray);
void		ray_loop(t_cub *cub);

//			sprite
void		sprite_size(t_player pl, t_sprite *spr);
void		draw_sprite_column(t_cub *cub, t_sprite sprite, int x);
void		order_sprites(t_cub *cub);
void		draw_sprites(t_cub *cub, t_player player, t_sprite *sprite);

//			texture
void		select_texture(t_cub *cub, t_texture *wall, t_ray ray);
void		texture_data(t_cub *cub, t_texture *wall,
				t_ray ray, double wall_dst);

//			utils 2
int			is_space(int character);
int			is_digit(int c);
int			is_alnum(int c);
int			is_alpha(int c);
int			is_float(char *line);

//			utils 3
void		*calloc_cub(size_t count, size_t size);
void		error_message(char *message, t_cub *cub, int fd);
void		put_str(char *s, int fd);
void		put_char(char c, int fd);
int			min(int n1, int n2);

//			utils
int			string_n_compare(char *s1, char *s2, unsigned int n);
char		*find_char(char *string, char c);
char		*str_dup(const char *s1);
int			str_len(const char *string);
int			atoi_cub(char *str);

#endif