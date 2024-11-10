/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/10 16:50:15 by kez-zoub         ###   ########.fr       */
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
	if (cos(angle) <= 1.0 && cos(angle) > 0) // right half of the cercle
	{
		ray->dir = 'E';
		ray->x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
		ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * Tan;
		xo = TILE;
		yo = -TILE * Tan;
	}
	else if (cos(angle) >= -1.0 && cos(angle) < 0) // left half of the cercle
	{
		ray->dir = 'W';
		ray->x = (((int)val.game->plyr_x / TILE) * TILE) - 0.00005;
		ray->y = val.game->plyr_y + (val.game->plyr_x - ray->x) * Tan;
		xo = -TILE;
		yo = TILE * Tan;
	}
	else // vertical line in the middle of the cercle
	{
		ray->x = val.game->plyr_x;
		ray->y = val.game->plyr_y;
		ray->dof = 20;
	}
	while (ray->dof < 20 && corresponding_tile(val, ray->x, ray->y) == 0)
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
	if (sin(angle) <= 1.0 && sin(angle) > 0)// upper half of the cercle
	{
		ray->dir = 'N';
		ray->y = (((int)val.game->plyr_y / TILE) * TILE) -0.00005;// val.game->plyr_y / TILE * TILE for exp: 53 will become 50
		ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * Tan;
		yo = -TILE;
		xo = -yo * Tan;
	}
	else if (sin(angle) >= -1.0 && sin(angle) < 0) // lower half of the cercle
	{
		ray->dir = 'S';
		ray->y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
		ray->x = val.game->plyr_x + (val.game->plyr_y - ray->y) * Tan;
		yo = TILE;
		xo = -yo * Tan;
	}
	else // horizontale line in the middle of the cercle
	{
		ray->x = val.game->plyr_x;
		ray->y = val.game->plyr_y;
		ray->dof = 20;
	}
	while (ray->dof < 20 && corresponding_tile(val, ray->x, ray->y) == 0)
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
		// draw_line(val, h_ray.x, h_ray.y, 0xff0000);
		ray->x = h_ray.x;
		ray->y = h_ray.y;
		ray->dist = h_ray.dist;
		ray->dof = h_ray.dof;
		ray->dir = h_ray.dir;
		return ;
	}
	// draw_line(val, v_ray.x, v_ray.y, 0xff0000);
	ray->x = v_ray.x;
	ray->y = v_ray.y;
	ray->dist = v_ray.dist;
	ray->dof = v_ray.dof;
	ray->dir = v_ray.dir;
}
