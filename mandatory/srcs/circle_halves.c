/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_halves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 02:44:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 18:51:07 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;

	ray->dir = 'E';
	ray->x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = TILE;
	yo = -TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y))
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	left_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;

	ray->dir = 'W';
	ray->x = (((int)val.game->plyr_x / TILE) * TILE);
	ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * angle_tan;
	xo = -TILE;
	yo = TILE * angle_tan;
	while (empty_space(val, ray->x - 1, ray->y))
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	upper_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;

	ray->dir = 'N';
	ray->y = (((int)val.game->plyr_y / TILE) * TILE);
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = -TILE;
	xo = TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y - 1))
	{
		ray->x += xo;
		ray->y += yo;
	}
}

void	lower_half(t_val val, t_ray *ray, double angle_tan)
{
	double	xo;
	double	yo;

	ray->dir = 'S';
	ray->y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
	ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * angle_tan;
	yo = TILE;
	xo = -TILE * angle_tan;
	while (empty_space(val, ray->x, ray->y))
	{
		ray->x += xo;
		ray->y += yo;
	}
}
