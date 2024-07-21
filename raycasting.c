/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/21 01:55:10 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_val val, float endX, float endY, int color)
{
	// double	deltaX = endX - val.game->plyr_x;
	// double	deltaY = endY - val.game->plyr_y;
	// printf("draw_line end point: x: %d, y: %d\n", endX, endY);
	double	deltaX = (endX - val.game->plyr_x) /MSCALE;
	double	deltaY = (endY - val.game->plyr_y) /MSCALE;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;

	// double	pixelX = val.game->plyr_x;
	// double	pixelY = val.game->plyr_y;
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

float	vertical_cast(t_val val, float *vx, float *vy, float angle, int ray_number)
{
	int	r, dof;
	float	x, y, xo, yo;
	float	Tan;

	r = 0;
	Tan = tan(angle);
	dof = 0;
	// while (r < 1)
	// {
		if ((angle > 0 && angle < PI / 2.0) || (angle > 3.0 * PI / 2.0 && angle < 2.0 * PI))
		{
			x = (((int)val.game->plyr_x / TILE) * TILE) + TILE;
			y = val.game->plyr_y + (val.game->plyr_x - x) * Tan;
			xo = TILE;
			yo = -TILE * Tan;
		}
		else if (angle > PI / 2 && angle < 3.0 * PI / 2.0)
		{
			x = (((int)val.game->plyr_x / TILE) * TILE) - 0.001;
			y = val.game->plyr_y + (val.game->plyr_x - x) * Tan;
			xo = -TILE;
			yo = TILE * Tan;
		}
		else
		{
			
		}
		r++;
	// }
	while (dof < 20)
	{
		if (!inside_empty_space(val, x, y))
			break;
		// {
		// 	dof = 20;
		// }
		x += xo;
		y += yo;
		dof++;
	}
	*vx = x;
	*vy = y;
	return (dist(val, x, y));
}

float	horizontal_cast(t_val val, float *hx, float *hy, float angle, int ray_number)
{
	int	r, dof;
	float	x, y, xo, yo;
	float	Tan;

	r = 0;
	Tan = 1 / tan(angle);
	// while (r < 1)
	// {
		dof = 0;
		if (angle < PI && angle > 0)// looking up
		{
			y = (((int)val.game->plyr_y / TILE) * TILE) -0.0001;// val.game->plyr_y / TILE * TILE for exp: 53 will become 50
			x = val.game->plyr_x + (val.game->plyr_y - y) * Tan;
			yo = -TILE;
			xo = -yo * Tan;
		}
		else if (angle > PI && angle < 2.0 * PI)
		{
			y = (((int)val.game->plyr_y / TILE) * TILE) + TILE;
			x = val.game->plyr_x + (val.game->plyr_y - y) * Tan;
			yo = TILE;
			xo = -yo * Tan;
		}
		else
		{
			x = val.game->plyr_x;
			y = val.game->plyr_y;
			dof = 20;
		}
		// r++;
	// }
	while (dof < 20)
	{
		if (!inside_empty_space(val, x, y))
			break;
		// {
		// 	dof = 20;
		// }
		x += xo;
		y += yo;
		dof++;
	}
	*hx = x;
	*hy = y;
	return (dist(val, x, y));
}


// float	cast_ray(t_val val, float *x, float *y, float angle, int ray_number)
float	cast_ray(t_val val,  float angle, int ray_number)
{
	float hx, hy, vx, vy;
	float	v_dest = vertical_cast(val, &vx, &vy, angle, ray_number);
	float	h_dest = horizontal_cast(val, &hx, &hy, angle, ray_number);
	
	if (h_dest <= v_dest)
	{
		draw_line(val, hx, hy, 0xff0000);
		return (h_dest);
	}
	draw_line(val, vx, vy, 0xff0000);
	return (v_dest);
	// printf("ray: x: %f, y: %f\n", x, y);
	// draw_line(val, x, y, 0xff0000);
}

void	draw_rays(t_val *val)
{
	// printf("tan(PI / 2 - PI / 100) : %f\n", tan(PI / 2 - PI / 100));
	float	x;
	float	y;
	int		i;
	float	angle;

	i = 0;
	// angle = val->game->plyr_dir;
	// cast_ray(*val, angle, i);
	
	angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (i < val->width)
	{
		val->rays[i] = cast_ray(*val, angle, i);
		// printf("final %d: x: %f, y: %f\n", i, round(x), round(y));
		// draw_line(*val, round(x), round(y), 0xff0000);
		i++;
		angle = limit_angle(angle - FOV / (float)(val->width -1));
	}
}
