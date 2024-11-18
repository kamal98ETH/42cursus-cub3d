/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_halves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:44:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/18 04:01:04 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_half(t_val val, t_ray *ray, float angle, float angle_tan)
{
	float	xo;
	float	yo;

	ray->dir = 'E';
	ray->x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = TILE;
	yo = -TILE * angle_tan;
	while (corresponding_tile(val, ray->x, ray->y) == 0)
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	left_half(t_val val, t_ray *ray, float angle, float angle_tan)
{
	float	xo;
	float	yo;

	ray->dir = 'W';
	ray->x = (((int)val.game->plyr_x / TILE) * TILE);
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = -TILE;
	yo = TILE * angle_tan;
	while (corresponding_tile(val, ray->x - 0.1, ray->y) == 0)
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	upper_half(t_val val, t_ray *ray, float angle, float angle_tan)
{
	float	xo;
	float	yo;

	ray->dir = 'N';
	ray->y = (((int)val.game->plyr_y / TILE) * TILE);
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = -TILE;
	xo = -yo * angle_tan;
	while (corresponding_tile(val, ray->x, ray->y - 0.1) == 0)
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	lower_half(t_val val, t_ray *ray, float angle, float angle_tan)
{
	float	xo;
	float	yo;

	ray->dir = 'S';
	ray->y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = TILE;
	xo = -yo * angle_tan;
	while (corresponding_tile(val, ray->x, ray->y) == 0)
	{
		ray->x += xo;
		ray->y += yo;
	}
}
