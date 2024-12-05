/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:57:29 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/04 21:35:05 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	empty_space(t_val val, float x, float y)
{
	char	c;

	c = corresponding_tile(val, x, y);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'X')
		return (1);
	else if (c == 'D')
		return (2);
	return (0);
}

int	check_for_doors(t_val *val, int x, int y)
{
	t_door	*door;

	if (!empty_space(*val, x, y))
		return (0);
	door = coordinate_to_door(*val, x, y);
	if (!door)
		return (1);
	// printf("here %p\n\n", door);
	if (door->state == OPEN)
	{
		door->state = CLOSED;
		return (1);
	}
	else
	{
		if (corresponding_tile(*val, val->game->plyr_x, val->game->plyr_y) == 'D')
			return (1);
		return (0);
	}
	
}
void apply_movement(t_val *val, float x, float y)
{
	if ((empty_space(*val, x, y) == 1 || check_for_doors(val, x, y))\
	 && (corresponding_tile(*val, val->game->plyr_x, y) != '1'\
	 || corresponding_tile(*val, x, val->game->plyr_y) != '1'))
	{
		val->game->plyr_x = x;
		val->game->plyr_y = y;
	}
	else if ((empty_space(*val, x, val->game->plyr_y) == '1' || check_for_doors(val, x, val->game->plyr_y)))
		val->game->plyr_x = x;
	else if ((empty_space(*val, val->game->plyr_x, y) == '1' || check_for_doors(val, val->game->plyr_x, y)))
		val->game->plyr_y = y;
}

void	move_player(t_val *val)
{
	float	x;
	float	y;
	int		flag;
	int		tmpx;
	int		tmpy;

	flag = 0;
	// mlx_mouse_get_pos(val->mlx_ptr, val->win_ptr, &tmpx, &tmpy);
	// if (tmpx >= val->width)
	// 	val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
	// else if (tmpx <= 0)
	// 	val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
	// else if (tmpx != val->tmpx)
	// 	val->game->plyr_dir = limit_angle(val->game->plyr_dir + (val->tmpx - tmpx) * 0.004f);
	// mlx_mouse_get_pos(val->mlx_ptr, val->win_ptr, &(val->tmpx), &(val->tmpy));
	if (val->keys[LA_K]) // left
		val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
	if (val->keys[RA_K])
		val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
	x = val->game->plyr_x;
	y = val->game->plyr_y;
	if (val->keys[W_K]) // forward 
	{
		// printf("forward\n");
		flag++;
		x += cos(val->game->plyr_dir) * MVTSPEED;
		y -= sin(val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[S_K]) // backward
	{
		// printf("backward\n");
		flag++;
		x -= cos(val->game->plyr_dir) * MVTSPEED;
		y += sin(val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[A_K]) // left
	{
		// printf("left\n");
		flag++;
		x -= cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y -= sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[D_K]) // right
	{
		// printf("right\n");
		flag++;
		x += cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y += sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (!flag)
		return ;
	apply_movement(val, x, y);
}

float	limit_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}


void	color_map_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	offset = y * val.map_data.sline + x * (val.map_data.bpp / 8);
	*(int *)(val.map_data.img_data + offset) = color;
}

void	color_game_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	if (color < 0)
		return ;
	offset = y * val.data.sline + x * (val.data.bpp / 8);
	*(int *)(val.data.img_data + offset) = color;
}

char	corresponding_tile(t_val val, float x, float y)
{
	int	X;
	int	Y;
	int	i;
	int	offset;

	X = floor(x / TILE);
	Y = floor(y / TILE);
	if (X < 0 || Y < 0 || X >= val.game->map_x || Y >= val.game->map_y)
		return (0);
	return (val.game->map[Y][X]);
}
