/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/05 22:24:49 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_val val, double endX, double endY, int color)
{
	double	start_x = MINIMAP_X /2;
	double	start_y = MINIMAP_Y /2;
	
	double	deltaX = (endX - val.game->plyr_x) /MSCALE;
	double	deltaY = (endY - val.game->plyr_y) /MSCALE;

	int	pixels = ceil(sqrt((deltaX * deltaX) + (deltaY * deltaY)));
	deltaX /= pixels;
	deltaY /= pixels;

	// Extract color components
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;

    while (pixels)
    {
		if (start_x < 0 || start_x >= MINIMAP_X || start_y < 0 || start_y >= MINIMAP_Y)
			return ;
        // Reduce color intensity for fading
        red *= FADEFACTOR;
        green *= FADEFACTOR;
        blue *= FADEFACTOR;

        // Recombine the faded color
        int faded_color = (red << 16) | (green << 8) | blue;

        color_map_pixel(val, ceil(start_x), ceil(start_y), faded_color);
        start_x += deltaX;
        start_y += deltaY;
        pixels--;
    }
}

void	vertical_cast(t_val val, t_ray *ray, double angle)
{
	double	angle_tan;

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

void	horizontal_cast(t_val val, t_ray *ray, double angle)
{
	double	angle_tan;

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

void	cast_ray(t_val val, t_ray *ray, double angle)
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
