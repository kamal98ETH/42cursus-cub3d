/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 02:08:13 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/21 14:06:42 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*coordinate_to_door(t_val val, float x, float y)
{
	int		X;
	int		Y;
	t_door	*door;

	X = floor(x / TILE);
	Y = floor(y / TILE);
	// printf("X: %d, Y: %d\n", X, Y);
	door = val.game->doors;
	while (door)
	{
		if ((door->tile_x == X && door->tile_y == Y))
			return (door);
		door = door->next;
	}
	return (NULL);
}

void	open_door_nearby(t_val val)
{
	int		X;
	int		Y;
	t_door	*door;

	X = val.game->plyr_x / TILE;
	Y = val.game->plyr_y / TILE;
	door = val.game->doors;
	while (door)
	{
		if ((door->tile_x == X && door->tile_y == Y -1)
			|| (door->tile_x == X && door->tile_y == Y +1)
			|| (door->tile_x == X -1 && door->tile_y == Y)
			|| (door->tile_x == X +1 && door->tile_y == Y))
		{
			door->state = OPEN;
			return ;
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
				return(1);
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