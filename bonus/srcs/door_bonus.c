/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:13 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/09 18:08:40 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_door_logic(char **str, int *flag)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'D')
			{
				if (!((j && str[i][j - 1] == '1') && str[i][j + 1] == '1') \
				&& !((i && str[i - 1][j] == '1') && (str[i + 1] \
				&& str[i + 1][j] == '1')))
				{
					*flag = -6;
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_for_doors(t_val *val, int x, int y, int flag)
{
	t_door	*current_door;
	t_door	*next_door;
	double	*tx;
	double	*ty;

	tx = &val->game->plyr_x;
	ty = &val->game->plyr_y;
	if (flag)
	{
		tx = &val->game->enemy_x;
		ty = &val->game->enemy_y;
	}
	if (!empty_space(*val, x, y))
		return (0);
	next_door = coordinate_to_door(*val, x, y);
	current_door = coordinate_to_door(*val, *tx, *ty);
	if (!next_door)
		return (1);
	if (next_door->state == OPEN)
		next_door->state = CLOSED;
	else if (current_door != next_door)
		return (0);
	return (1);
}

int	door_init(t_val *val)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	val->game->doors = NULL;
	while (y < val->game->map_y)
	{
		while (x < val->game->map_x)
		{
			if (val->game->map[y][x] == 'D')
				if (push_door_list(val, x, y))
					return (1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
