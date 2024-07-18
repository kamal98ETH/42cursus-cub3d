/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:23 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/18 13:24:36 by kez-zoub         ###   ########.fr       */
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
#define STILE 256
#define	RAYS 1280
#define	MVTSPEED 20
#define RTTSPEED .2
#define PI 3.1415926535
#define FOV PI / 2.0
#define EPSILON 0.01

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
	int		plyr_x;
	int		plyr_y;
	float	plyr_dir;
	char	*map;
	int		map_x;
	int		map_y;
}	t_game;

typedef struct s_val
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_map_ptr;
	int		width;
	int		height;
	float	*rays;
	t_game	*game;
}	t_val;

void	draw_map(t_val *val);
void	render(t_val *val);
float	limit_angle(float angle);
void	draw_rays(t_val *val);
int	inside_empty_space(t_val val, float x, float y);
t_tile	coordinates_to_tile(int x, int y, char *map);
void	color_map_pixel(t_val val, int x, int y, int color);
void	color_game_pixel(t_val val, int x, int y, int color);
void	render(t_val *val);

#endif