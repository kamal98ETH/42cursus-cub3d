/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:13 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 15:49:46 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_door	*door;
	t_game	*g;

	g = val->game;
	if (!empty_space(*val, x, y))
		return (0);
	door = coordinate_to_door(*val, x, y);
	if (!door)
		return (1);
	if (door->state == OPEN)
	{
		door->state = CLOSED;
		return (1);
	}
	if (flag && corresponding_tile(*val, g->enemy_x, g->enemy_y) == 'D')
		return (1);
	else if (corresponding_tile(*val, g->plyr_x, g->plyr_y) == 'D')
		return (1);
	return (0);
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
