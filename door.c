/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:13 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/23 01:07:31 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	door_init(t_val *val)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	val->game->doors = NULL;
	while (i < val->game->map_size)
	{
		if (val->game->map[i] == 'D')
			if (push_door_list(val, x, y))
				return (1);
		if (val->game->map[i] == '\n')
		{
			x = -1;
			y++;
		}
		x++;
		i++;
	}
	return (0);
}
