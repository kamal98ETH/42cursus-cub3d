/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:57:29 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 18:52:31 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	angle_movement(t_val *val)
{
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
	apply_movement(val, x, y);
}
