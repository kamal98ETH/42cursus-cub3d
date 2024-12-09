/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:23 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 19:01:55 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include "../../MiniLibX/mlx.h"
# include "../../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>	
# include <limits.h>

# define HEIGHT 800
# define WIDTH 1000

# define TILE 200
# define MSCALE 10
# define MVTSPEED 12
# define RTTSPEED .03
# define PI 3.1415926535
# define FOV 1.0471975512
# define MINIMAP_X 200
# define MINIMAP_Y 150

# define W_KEYCODE 119
# define S_KEYCODE 115
# define A_KEYCODE 97
# define D_KEYCODE 100
# define RA_KEYCODE 65363
# define LA_KEYCODE 65361
# define ESC_KEYCODE 65307

# define W_K 0
# define S_K 1
# define A_K 2
# define D_K 3
# define LA_K 4
# define RA_K 5

typedef struct s_col
{
	int	stat;
	int	hexacode;
}	t_col;

typedef struct s_data
{
	void	*img;
	char	*img_data;
	int		bpp;
	int		sline;
	int		endian;
}	t_data;

typedef struct s_texture
{
	char	*path;
	int		width;
	int		height;
	t_data	img;
}	t_texture;

typedef struct s_pos
{
	int	plr_x;
	int	plr_y;
}	t_pos;

typedef struct s_game
{
	t_texture	no;
	t_texture	we;
	t_texture	ea;
	t_texture	so;
	t_col		fcol;
	t_col		ccol;
	double		plyr_x;
	double		plyr_y;
	double		plyr_dir;
	char		**map;
	int			map_x;
	int			map_y;
}	t_game;

typedef struct s_ray
{
	double	x;
	double	y;
	double	dist;
	char	dir;
}	t_ray;

typedef struct s_val
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_data	data;
	t_game	*game;
	int		keys[6];
}	t_val;

/* rendering */
int		render(t_val *val);
double	limit_angle(double angle);
char	corresponding_tile(t_val val, double x, double y);
int		empty_space(t_val val, double x, double y);
void	color_game_pixel(t_val val, int x, int y, int color);

/* movement */
void	move_player(t_val *val);
void	apply_movement(t_val *val, double x, double y);
void	angle_movement(t_val *val);

/* raycasting*/
void	right_half(t_val val, t_ray *ray, double angle_tan);
void	left_half(t_val val, t_ray *ray, double angle_tan);
void	upper_half(t_val val, t_ray *ray, double angle_tan);
void	lower_half(t_val val, t_ray *ray, double angle_tan);
void	cast_ray(t_val val, t_ray *ray, double angle);

/* parsing .... */
void	get_player_position(t_game *map);
void	get_player_direction(t_game *map, char flag);
t_game	*data_treatment(char **arr, char *content);
char	**square_format(char **str, t_game *map);
int		get_elements(t_game *map, char *str, int flag);
int		fetch_texture(t_game *map, char **elems, int flag);
int		fetch_color(t_game *map, char **elems, int opt);
t_game	*parsing(char *filename);

/* check functions related to parsing */
int		check_map_validation(char **str, int *i);
int		coma_check(char *str);
int		check_name(char	*str);
int		check_if_map(char *str);

/* map treatment functions */
int		map_init(t_game **map);
t_game	*get_map(char **str, char *content, t_game *map);
void	handle_map_error(int flag);
char	*get_data(char *str);
void	free_map(t_game *map);

/* utils functions to help with parsing */
int		valid(int c);
int		is_whitespace(int c);
void	ft_free(char **arr);
int		unique_atoi(const char *str, int *flag);
char	*join_optclean(char *s1, char *s2, int flag);
char	**multi_split(char const *s, char *c);

/* texture functions */
void	ft_open_textures(t_val *val);
int		txtr_fetch(t_texture *txtr, t_ray ray, double y, double wall_height);
int		color_fetched(t_val *val, t_ray ray, double y, double wall_height);

/* hooks */
void	mlx_hooks(t_val *val);

/* cleaning functions */
void	img_destructor(void *mlx_ptr, void *img_ptr);
void	ft_clean(t_val *val);

#endif