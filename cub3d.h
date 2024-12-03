/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:23 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/03 22:55:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H


# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>



#include "MiniLibX/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>	
#include <limits.h>

#define TILE 200
#define	MSCALE 16
#define	MVTSPEED TILE / 20
#define	ENYSPEED TILE / 30
#define RTTSPEED .04
#define PI 3.1415926535
#define FOV PI / 3.0
#define MINIMAP_X 200
#define MINIMAP_Y 150

#define	W_KEYCODE 119
#define	S_KEYCODE 115
#define	A_KEYCODE 97
#define	D_KEYCODE 100
#define	RA_KEYCODE 65363
#define	LA_KEYCODE 65361
#define	ESC_KEYCODE	65307
#define	E_KEYCODE 101

#define	W_K 0
#define	S_K 1
#define	A_K 2
#define	D_K 3
#define	LA_K 4
#define	RA_K 5

typedef enum e_dstate
{
	OPEN,
	CLOSED
}	t_dstate;

typedef struct	s_col
{
	int	stat;
	int	hexacode;
}	t_col;

typedef struct s_door
{
	int				tile_x;
	int				tile_y;
	t_dstate		state;
	struct s_door	*next;
}	t_door;

typedef	struct	s_data
{
	void	*img;
	char	*img_data;
	int		bpp;
	int		sline;
	int		endian;
}	t_data;

typedef struct	s_texture
{
	char	*path;
	int		width;
	int		height;
	t_data	img;
}	t_texture;

typedef struct	s_pos
{
	int	plr_x;
	int	plr_y;
}	t_pos;

typedef	struct s_game
{
	t_texture	no;
	t_texture	we;
	t_texture	ea;
	t_texture	so;
	t_texture	dr;
	t_texture	df;
	t_texture	en;  //enemy
	t_col		fcol;
	t_col		ccol;
	float		plyr_x;
	float		plyr_y;
	float		enemy_x; //enemy
	float		enemy_y; //enemy
	float		enemy_dir; //enemy
	float		plyr_dir;
	float		dist;
	char		**map;
	int			map_size;
	int			map_x;
	int			map_y;
	t_door		*doors;
}	t_game;

typedef struct s_ray
{
	double	x;
	double	y;
	float	dist;
	char	dir;
	char	door;
}	t_ray;

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
	int		keys[6];
	int		start;

	int		tmpx;
	int		tmpy;
}	t_val;

void	draw_map(t_val *val);
int		render(t_val *val);
float	limit_angle(float angle);
char	corresponding_tile(t_val val, float x, float y);
int		empty_space(t_val val, float x, float y);
void	color_map_pixel(t_val val, int x, int y, int color);
void	color_game_pixel(t_val val, int x, int y, int color);

void	move_player(t_val *val);

/* raycasting*/
void	right_half(t_val val, t_ray *ray, float angle, float angle_tan);
void	left_half(t_val val, t_ray *ray, float angle, float angle_tan);
void	upper_half(t_val val, t_ray *ray, float angle, float angle_tan);
void	lower_half(t_val val, t_ray *ray, float angle, float angle_tan);
void	cast_ray(t_val val, t_ray *ray, float angle);

/* doors*/
int		door_init(t_val *val);
int		clean_doors(t_door *doors);
t_door	*coordinate_to_door(t_val val, float x, float y);
void	open_door_nearby(t_val val);
int		push_door_list(t_val *val, int x, int y);

/* parsing .... */
void	get_player_position(t_game *map);
void	get_player_direction(t_game *map, char flag);
int		get_enemy_position(t_game *map);
t_game	*data_treatment(char **arr, char *content);
char	**square_format(char **str, t_game *map);
int		get_elements(t_game *map, char *str);
int 	fetch_texture(t_game *map, char **elems, int flag);
int 	fetch_color(t_game *map, char **elems, int opt);
t_game	*parsing(char *filename);

/* map treatment functions */
void	map_init(t_game *map);
t_game	*get_map(char **str, char *content, t_game *map);
void	handle_map_error(int flag);
char	*get_data(char *str);
void	free_map(t_game *map);

/* check functions related to parsing */
int		check_map_validation(char **str, int *i);
int		coma_check(char *str);
int		check_name(char	*str);
int		check_if_map(char *str);

/* utils functions to help with parsing */
int		valid(int c);
int		is_whitespace(int c);
void	ft_free(char **arr);
int		unique_atoi(const char *str, int *flag);
char	*join_optclean(char *s1, char *s2, int flag);
char	**multi_split(char const *s, char *c);

/* texture functions */
void	ft_open_textures(t_val *val);
int		txtr_fetch(t_texture *txtr, t_ray ray, float y, float wall_height);

/* hooks */
void	mlx_hooks(t_val *val);

void	check_death(t_val *val);

#endif