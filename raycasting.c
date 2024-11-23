/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/22 11:13:07 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_line(t_val val, float endX, float endY, int color)
// {
// 	double	deltaX = (endX - val.game->plyr_x) /MSCALE;
// 	double	deltaY = (endY - val.game->plyr_y) /MSCALE;

// 	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;
// 	double	pixelX = val.game->plyr_x /MSCALE;
// 	double	pixelY = val.game->plyr_y /MSCALE;
// 	while (pixels)
// 	{
// 		color_map_pixel(val, round(pixelX), round(pixelY), color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		pixels--;
// 	}
// }

void	vertical_cast(t_val val, t_ray *ray, float angle)
{
	float	angle_tan;

	angle_tan = tan(angle);
	if (cos(angle) <= 1.0 && cos(angle) > 0)
		right_half(val, ray, angle, angle_tan);
	else if (cos(angle) >= -1.0 && cos(angle) < 0)
		left_half(val, ray, angle, angle_tan);
	else
	{
		ray->x = INFINITY;
		ray->y = INFINITY;
	}
	ray->dist = sqrt(pow(ray->x - val.game->plyr_x, 2)
			+ pow(ray->y - val.game->plyr_y, 2));
}

void	horizontal_cast(t_val val, t_ray *ray, float angle)
{
	float	angle_tan;

	angle_tan = 1 / tan(angle);
	if (sin(angle) <= 1.0 && sin(angle) > 0)
		upper_half(val, ray, angle, angle_tan);
	else if (sin(angle) >= -1.0 && sin(angle) < 0)
		lower_half(val, ray, angle, angle_tan);
	else
	{
		ray->x = INFINITY;
		ray->y = INFINITY;
	}
	ray->dist = sqrt(pow(ray->x - val.game->plyr_x, 2)
			+ pow(ray->y - val.game->plyr_y, 2));
}

void	cast_ray(t_val val, t_ray *ray, float angle)
{
	t_ray	h_ray;
	t_ray	v_ray;

	vertical_cast(val, &v_ray, angle);
	horizontal_cast(val, &h_ray, angle);
	if (h_ray.dist < v_ray.dist)
	{
		ray->x = h_ray.x;
		ray->y = h_ray.y;
		ray->dist = h_ray.dist;
		ray->dir = h_ray.dir;
		ray->door = h_ray.door;
		return ;
	}
	ray->x = v_ray.x;
	ray->y = v_ray.y;
	ray->dist = v_ray.dist;
	ray->dir = v_ray.dir;
	ray->door = v_ray.door;
}
