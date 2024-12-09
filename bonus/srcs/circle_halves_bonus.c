/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_halves_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:44:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 17:46:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	right_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;
	t_door	*door;

	ray->dir = 'E';
	ray->door = 0;
	ray->x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = TILE;
	yo = -TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y))
	{
		door = coordinate_to_door(val, ray->x, ray->y);
		if (door && door->state == CLOSED)
		{
			ray->x += TILE / 2;
			ray->y -= TILE / 2 * angle_tan;
			ray->door = 'D';
			return ;
		}
		ray->x += xo;
		ray->y += yo;
	}
	if (empty_space(val, ray->x -1, ray->y) == 2)
		ray->door = 'd';
}

void	left_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;
	t_door	*door;

	ray->dir = 'W';
	ray->door = 0;
	ray->x = (((int)val.game->plyr_x / TILE) * TILE);
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = -TILE;
	yo = TILE * angle_tan;
	while (empty_space(val, ray->x - 1, ray->y))
	{
		door = coordinate_to_door(val, ray->x - 1, ray->y);
		if (door && door->state == CLOSED)
		{
			ray->x -= TILE / 2;
			ray->y += TILE / 2 * angle_tan;
			ray->door = 'D';
			return ;
		}
		ray->x += xo;
		ray->y += yo;
	}
	if (empty_space(val, ray->x + 1, ray->y) == 2)
		ray->door = 'd';
}

void	upper_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;
	t_door	*door;

	ray->dir = 'N';
	ray->door = 0;
	ray->y = (((int)val.game->plyr_y / TILE) * TILE);
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = -TILE;
	xo = TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y - 1))
	{
		door = coordinate_to_door(val, ray->x, ray->y - 1);
		if (door && door->state == CLOSED)
		{
			ray->x += TILE / 2 * angle_tan;
			ray->y -= TILE / 2;
			ray->door = 'D';
			return ;
		}
		ray->x += xo;
		ray->y += yo;
	}
	if (empty_space(val, ray->x, ray->y + 1) == 2)
		ray->door = 'd';
}

void	lower_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;
	t_door	*door;

	ray->dir = 'S';
	ray->door = 0;
	ray->y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = TILE;
	xo = -TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y))
	{
		door = coordinate_to_door(val, ray->x, ray->y);
		if (door && door->state == CLOSED)
		{
			ray->x -= TILE / 2 * angle_tan;
			ray->y += TILE / 2;
			ray->door = 'D';
			return ;
		}
		ray->x += xo;
		ray->y += yo;
	}
	if (empty_space(val, ray->x, ray->y - 1) == 2)
		ray->door = 'd';
}
