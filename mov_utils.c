/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:16:00 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/06 17:20:11 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_movement(t_val *val, double x, double y, int flag)
{
	double	*x_corr;
	double	*y_corr;

	x_corr = &(val->game->plyr_x);
	y_corr = &(val->game->plyr_y);
	if (flag)
	{
		x_corr = &(val->game->enemy_x);
		y_corr = &(val->game->enemy_y);
	}
	if ((empty_space(*val, x, y) == 1 || check_for_doors(val, x, y, flag)) \
	&& (corresponding_tile(*val, *x_corr, y) != '1' \
	|| corresponding_tile(*val, x, *y_corr) != '1'))
	{
		*x_corr = x;
		*y_corr = y;
	}
	else if ((empty_space(*val, x, *y_corr) == '1'
			|| check_for_doors(val, x, *y_corr, flag)))
		*x_corr = x;
	else if ((empty_space(*val, *x_corr, y) == '1'
			|| check_for_doors(val, *x_corr, y, flag)))
		*y_corr = y;
}

int	empty_space(t_val val, double x, double y)
{
	char	c;

	c = corresponding_tile(val, x, y);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'X')
		return (1);
	else if (c == 'D')
		return (2);
	return (0);
}

double	limit_angle(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

char	corresponding_tile(t_val val, double x, double y)
{
	int	c_x;
	int	c_y;
	int	i;
	int	offset;

	c_x = floor(x / TILE);
	c_y = floor(y / TILE);
	if (c_x < 0 || c_y < 0 || c_x >= val.game->map_x || c_y >= val.game->map_y)
		return (0);
	return (val.game->map[c_y][c_x]);
}
