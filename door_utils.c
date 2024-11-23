/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 01:05:46 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/23 01:06:30 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*coordinate_to_door(t_val val, float x, float y)
{
	int		x_tile;
	int		y_tile;
	t_door	*door;

	x_tile = floor(x / TILE);
	y_tile = floor(y / TILE);
	door = val.game->doors;
	while (door)
	{
		if ((door->tile_x == x_tile && door->tile_y == y_tile))
			return (door);
		door = door->next;
	}
	return (NULL);
}

void	open_door_nearby(t_val val)
{
	int		x_tile;
	int		y_tile;
	t_door	*door;

	x_tile = val.game->plyr_x / TILE;
	y_tile = val.game->plyr_y / TILE;
	door = val.game->doors;
	while (door)
	{
		if ((sin(val.game->plyr_dir) <= 1.0 && sin(val.game->plyr_dir) > 0
				&& door->tile_x == x_tile && door->tile_y == y_tile -1)
			|| (sin(val.game->plyr_dir) >= -1.0 && sin(val.game->plyr_dir) < 0
				&& door->tile_x == x_tile && door->tile_y == y_tile +1)
			|| (cos(val.game->plyr_dir) >= -1.0 && cos(val.game->plyr_dir) < 0
				&& door->tile_x == x_tile -1 && door->tile_y == y_tile)
			|| (cos(val.game->plyr_dir) <= 1.0 && cos(val.game->plyr_dir) > 0
				&& door->tile_x == x_tile +1 && door->tile_y == y_tile))
		{
			door->state = OPEN;
		}
		door = door->next;
	}
}

t_door	*new_door(int x, int y)
{
	t_door	*door;

	door = (t_door *)malloc(sizeof(t_door));
	if (!door)
		return (NULL);
	door->tile_x = x;
	door->tile_y = y;
	door->state = CLOSED;
	door->next = NULL;
	return (door);
}

int	clean_doors(t_door *doors)
{
	t_door	*tmp;

	while (doors)
	{
		tmp = doors;
		doors = doors->next;
		free(tmp);
	}
	return (1);
}

int	push_door_list(t_val *val, int x, int y)
{
	t_door	*door;
	t_door	*it;

	door = new_door(x, y);
	if (!door)
		return (clean_doors(val->game->doors));
	if (!val->game->doors)
		val->game->doors = door;
	else
	{
		it = val->game->doors;
		while (it->next)
		{
			it = it->next;
		}
		it->next = door;
	}
	return (0);
}
