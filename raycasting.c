/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/10/25 20:14:15 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_val val, float endX, float endY, int color)
{
	double	deltaX = (endX - val.game->plyr_x) /MSCALE;
	double	deltaY = (endY - val.game->plyr_y) /MSCALE;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double	pixelX = val.game->plyr_x /MSCALE;
	double	pixelY = val.game->plyr_y /MSCALE;
	while (pixels)
	{
		color_map_pixel(val, round(pixelX), round(pixelY), color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
}

float	dist(t_val val, float x, float y)
{
	return (sqrt(pow(x - val.game->plyr_x, 2) + pow(y - val.game->plyr_y, 2)));
}

void	vertical_cast(t_val val, t_ray *ray, float angle)
{
	float	xo;
	float	yo;
	float	Tan;

	Tan = tan(angle);
	ray->dof = 0;
	if ((angle > 0 && angle < PI / 2.0) || (angle > 3.0 * PI / 2.0 && angle < 2.0 * PI))
	{
		ray->dir = 'E';
		ray->x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
		ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * Tan;
		xo = TILE;
		yo = -TILE * Tan;
	}
	else if (angle > PI / 2 && angle < 3.0 * PI / 2.0)
	{
		ray->dir = 'W';
		ray->x = (((int)val.game->plyr_x / TILE) * TILE) - 0.001;
		ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * Tan;
		xo = -TILE;
		yo = TILE * Tan;
	}
	else
	{
		ray->x = val.game->plyr_x;
		ray->y = val.game->plyr_y;
		ray->dof = 20;
	}
	while (ray->dof < 20 && inside_empty_space(val, ray->x, ray->y))
	{
		ray->x += xo;
		ray->y += yo;
		ray->dof++;
	}
	ray->dist = dist(val, ray->x, ray->y);
}

void	horizontal_cast(t_val val, t_ray *ray, float angle)
{
	float	xo;
	float	yo;
	float	Tan;

	Tan = 1 / tan(angle);
	ray->dof = 0;
	if (angle < PI && angle > 0)// looking up
	{
		ray->dir = 'N';
		ray->y = (((int)val.game->plyr_y / TILE) * TILE) -0.0001;// val.game->plyr_y / TILE * TILE for exp: 53 will become 50
		ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * Tan;
		yo = -TILE;
		xo = -yo * Tan;
	}
	else if (angle > PI && angle < 2.0 * PI)
	{
		ray->dir = 'S';
		ray->y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
		ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * Tan;
		yo = TILE;
		xo = -yo * Tan;
	}
	else
	{
		ray->x = val.game->plyr_x;
		ray->y = val.game->plyr_y;
		ray->dof = 20;
	}
	while (ray->dof < 20 && inside_empty_space(val, ray->x, ray->y))
	{
		ray->x += xo;
		ray->y += yo;
		ray->dof++;
	}
	ray->dist = dist(val, ray->x, ray->y);
}


void	cast_ray(t_val val, t_ray *ray, float angle)
{
	t_ray	h_ray;
	t_ray	v_ray;

	vertical_cast(val, &v_ray, angle);
	horizontal_cast(val, &h_ray, angle);
	
	if (h_ray.dist <= v_ray.dist)
	{
		draw_line(val, h_ray.x, h_ray.y, 0xff0000);
		ray->x = h_ray.x;
		ray->y = h_ray.y;
		ray->dist = h_ray.dist;
		ray->dof = h_ray.dof;
		ray->dir = h_ray.dir;
		return ;
	}
	draw_line(val, v_ray.x, v_ray.y, 0xff0000);
	ray->x = v_ray.x;
	ray->y = v_ray.y;
	ray->dist = v_ray.dist;
	ray->dof = v_ray.dof;
	ray->dir = v_ray.dir;
}
