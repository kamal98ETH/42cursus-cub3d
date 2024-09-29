/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:23 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/09/29 16:38:10 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "MiniLibX/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>

#define TILE 40
#define	MSCALE 4
#define	MVTSPEED 10
#define RTTSPEED .2
#define PI 3.1415926535
#define FOV PI / 2.0

typedef struct	s_col
{
	int	stat;
	int	hexacode;
}	t_col;


typedef struct	s_texture
{
	char	*path;
}	t_texture;

typedef struct	s_pos
{
	int	plr_x;
	int	plr_y;
}	t_pos;

typedef struct s_coordinates
{
	int	x;
	int	y;
}	t_coordinates;

typedef struct s_tile
{
	int		x;
	int		y;
	char	c;
}	t_tile;

typedef	struct s_game
{
	t_texture	no;
	t_texture	we;
	t_texture	ea;
	t_texture	so;
	t_col		fcol;
	t_col		ccol;
	float	plyr_x;
	float	plyr_y;
	float	plyr_dir;
	char	*map;
	int		map_size;
	int		map_x;
	int		map_y;
}	t_game;

typedef struct s_ray
{
	float	x;
	float	y;
	int		dof;
	float	dist;
	char	dir;
}	t_ray;

typedef	struct	s_data
{
	char	*img_data;
	int		bpp;
	int		sline;
	int		endian;
}	t_data;

typedef struct s_val
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_map_ptr;
	t_data	data;
	t_data	map_data;
	int		width;
	int		height;
	t_game	*game;
}	t_val;

void	draw_map(t_val *val);
int		render(t_val *val);
float	limit_angle(float angle);
void	cast_ray(t_val val, t_ray *ray, float angle);
int		inside_empty_space(t_val val, float x, float y);
t_tile	coordinates_to_tile(float x, float y, char *map);
void	color_map_pixel(t_val val, int x, int y, int color);
void	color_game_pixel(t_val val, int x, int y, int color);

/* parsing .... */
void	get_player_position(t_game *map, char **tmp);
void	get_player_direction(t_game *map, char flag);
t_game	*data_treatment(char **arr, char *content);
char	**square_format(char **str);
char	*reformate(char *str);
int		get_elements(t_game *map, char *str);
int 	fetch_texture(t_game *map, char **elems, int flag);
int 	fetch_color(t_game *map, char **elems, int opt);
t_game	*parsing(char *filename);

/* map treatment functions */
void	map_init(t_game *map);
void	get_map(char **str, char *content, t_game *map);
void	handle_map_error(int flag);
char	*get_data(char *str);
void	free_game(t_game *map);

/* check functions related to parsing */
int		check_map_validation(char **str, int *i);
int		coma_check(char *str);
int		check_name(char	*str);
int		check_if_map(char *str);

/* utils functions to help with parsing */
int		valid_chars(int c);
int		is_whitespace(int c);
void	ft_free(char **arr);
int		unique_atoi(const char *str, int *flag);
char	*join_optclean(char *s1, char *s2, int flag);

/* split functions */
char	**multi_split(char const *s, char *c);

#endif