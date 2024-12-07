/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:57:29 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/07 11:57:01 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angle_movement(t_val *val)
{
	int		tmpx;
	int		tmpy;

	mlx_mouse_get_pos(val->mlx_ptr, val->win_ptr, &tmpx, &tmpy);
	if (tmpx >= WIDTH)
		val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
	else if (tmpx <= 0)
		val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
	else if (tmpx != val->tmpx)
		val->game->plyr_dir = limit_angle(val->game->plyr_dir + \
		(val->tmpx - tmpx) * 0.004f);
	mlx_mouse_get_pos(val->mlx_ptr, val->win_ptr, &(val->tmpx), &(val->tmpy));
	if (val->keys[LA_K])
		val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
	if (val->keys[RA_K])
		val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
}

int	move_2(t_val *val, double *x, double *y)
{
	int		flag;

	flag = 0;
	if (val->keys[A_K])
	{
		flag++;
		*x -= cos(PI / 2 - val->game->plyr_dir) * MVTSPEED;
		*y -= sin(PI / 2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[D_K])
	{
		flag++;
		*x += cos(PI / 2 - val->game->plyr_dir) * MVTSPEED;
		*y += sin(PI / 2 - val->game->plyr_dir) * MVTSPEED;
	}
	return (flag);
}

void	move_enemy(t_val *val)
{
	double	dx;
	double	dy;
	double	angle;

	dx = val->game->enemy_x - val->game->plyr_x;
	dy = val->game->enemy_y - val->game->plyr_y;
	val->game->dist = sqrt(pow(dx, 2) + pow(dy, 2)) / TILE;
	val->game->enemy_dir = -(double)atan2(dy, dx);
	val->game->enemy_dir = limit_angle(val->game->enemy_dir);
	dx = (-dx) * (ENYSPEED / (val->game->dist * TILE));
	dy = (-dy) * (ENYSPEED / (val->game->dist * TILE));
	dx = val->game->enemy_x + dx;
	dy = val->game->enemy_y + dy;
	apply_movement(val, dx, dy, 1);
}

void	move_player(t_val *val)
{
	double	x;
	double	y;
	int		flag;

	flag = 0;
	angle_movement(val);
	x = val->game->plyr_x;
	y = val->game->plyr_y;
	if (val->keys[W_K])
	{
		flag++;
		x += cos(val->game->plyr_dir) * MVTSPEED;
		y -= sin(val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[S_K])
	{
		flag++;
		x -= cos(val->game->plyr_dir) * MVTSPEED;
		y += sin(val->game->plyr_dir) * MVTSPEED;
	}
	flag += move_2(val, &x, &y);
	if (!flag)
		return ;
	apply_movement(val, x, y, 0);
}
