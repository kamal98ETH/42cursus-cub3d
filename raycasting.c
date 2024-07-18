/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:45:51 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/18 13:30:23 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// first method of ray casting
// void	draw_line(t_val val, int map, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double	deltaX = endX - beginX;
// 	double	deltaY = endY - beginY;

// 	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;

// 	double	pixelX = beginX;
// 	double	pixelY = beginY;
	
// 	int	coordinates[2];
// 	while (pixels)
// 	{
// 		coordinates[0] = pixelX;
// 		coordinates[1] = pixelY;
// 		color_pixel(val, map, coordinates, color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		pixels--;
// 	}
	
// }

// float	draw_ray(t_val val, double angle)
// {
// 	float length = 1;
// 	char c;
// 	float x0 = val.game->plyr_x;
// 	float y0 = val.game->plyr_y;
// 	float x1;
// 	float y1;

// 	// calculate line len
// 	x1 = x0 + length * cos(angle);
// 	y1 = y0 - length * sin(angle);
// 	while (inside_empty_space(val, round(x1), round(y1)))
// 	{
// 		length++;
// 		x1 = x0 + length * cos(angle);
// 		y1 = y0 - length * sin(angle); // - instead of + like the previous is becouse y axis is the opposite direction of a normal plan
// 	}
// 	length--;
// 	x1 = x0 + length * cos(angle);
// 	y1 = y0 - length * sin(angle);
// 	draw_line(val, 1, round(x0), round(y0), round(x1), round(y1), 0xff00ff);
	
// 	return (length);
// }

// void	draw_rays(t_val *val)
// {
// 	float	angle;
// 	int		i;
// 	// int		*rays;

// 	angle = limit_angle(val->game->plyr_dir + FOV /2);
// 	i = 0;
// 	while (i < RAYS)
// 	{
// 		val->rays[i] = draw_ray(*val, angle);
// 		angle = limit_angle(angle - FOV / RAYS);
// 		i++;
// 	}
// 	// return (rays);
// }
//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
//	second method of ray casting
// void	draw_line(t_val val, int map, int beginX, int beginY, int endX, int endY, int color)
// {
// 	double	deltaX = (endX - beginX) /10;
// 	double	deltaY = (endY - beginY) /10;

// 	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;

// 	double	pixelX = beginX;
// 	double	pixelY = beginY;
	
// 	while (pixels)
// 	{
// 		color_map_pixel(val, pixelX, pixelY, color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		pixels--;
// 	}
	
// }

// void	horizontal_hit(t_val *val, float ray_angle, int *h_x, int *h_y)
// {
// 	if (ray_angle <= EPSILON || ray_angle >= 2 * PI - EPSILON
// 		|| (ray_angle <= PI + EPSILON && ray_angle >= PI - EPSILON))
// 	{
// 		*h_x = val->game->map_x;
// 		*h_y = val->game->map_y;
// 	}
// 	else if (ray_angle < PI) // player looking up
// 	{
// 		*h_y = val->game->plyr_y - (val->game->plyr_y % TILE) -1;
// 		*h_x = val->game->plyr_x + (val->game->plyr_y - *h_y) / tan(ray_angle);
// 		while (inside_empty_space(*val, *h_x, *h_y))
// 		{
// 			*h_y -= TILE;
// 			*h_x = val->game->plyr_x + (val->game->plyr_y - *h_y) / tan(ray_angle);
// 		}
// 		(*h_y)++;
// 		*h_x = val->game->plyr_x + (val->game->plyr_y - *h_y) / tan(ray_angle);
// 	}
// 	else
// 	{
// 		*h_y = val->game->plyr_y + TILE - (val->game->plyr_y % TILE);
// 		*h_x = val->game->plyr_x + (val->game->plyr_y - *h_y) / tan(ray_angle);
// 		while (inside_empty_space(*val, *h_x, *h_y))
// 		{
// 			*h_y += TILE;
// 			*h_x = val->game->plyr_x + (val->game->plyr_y - *h_y) / tan(ray_angle);
// 		}
// 	}
// }

// void	vertical_hit(t_val *val, float ray_angle, int *v_x, int *v_y)
// {
// 	if ((ray_angle > PI / 2 - EPSILON && ray_angle < PI /2 + EPSILON)
// 		|| (ray_angle > 3 * PI / 2 - EPSILON && ray_angle < 3 * PI / 2 + EPSILON))
// 	{
// 		printf("vertical infinity\n");
// 		*v_x = val->game->map_x;
// 		*v_y = val->game->map_y;
// 	}
// 	else if (ray_angle < PI / 2 || ray_angle > 3 * PI / 2)
// 	{
// 		*v_x = val->game->plyr_x + TILE - val->game->plyr_x % TILE;
// 		*v_y = val->game->plyr_y - (*v_x - val->game->plyr_x) * tan(ray_angle);
// 		while (inside_empty_space(*val, *v_x, *v_y))
// 		{
// 			*v_x += TILE;
// 			*v_y = val->game->plyr_y - (*v_x - val->game->plyr_x) * tan(ray_angle);
// 		}
// 	}
// 	else
// 	{
// 		*v_x = val->game->plyr_x - val->game->plyr_x % TILE -1;
// 		*v_y = val->game->plyr_y - (*v_x - val->game->plyr_x) * tan(ray_angle);
// 		while (inside_empty_space(*val, *v_x, *v_y))
// 		{
// 			*v_x -= TILE;
// 			*v_y = val->game->plyr_y - (*v_x - val->game->plyr_x) * tan(ray_angle);
// 		}
// 		(*v_x)++;
// 		*v_y = val->game->plyr_y - (*v_x - val->game->plyr_x) * tan(ray_angle);
// 	}
// }

// float	draw_one_ray(t_val *val, float angle)
// {
// 	int	h_x;
// 	int	h_y;
// 	int	v_x;
// 	int	v_y;

// 	horizontal_hit(val, angle, &h_x, &h_y);
// 	vertical_hit(val, angle, &v_x, &v_y);
// 	printf("horizontal hit: %f, vertical hit; %f\n", sqrt((h_x - val->game->plyr_x) * (h_x - val->game->plyr_x) + (h_y - val->game->plyr_y) * (h_y - val->game->plyr_y)), sqrt((v_x - val->game->plyr_x) * (v_x - val->game->plyr_x) + (v_y - val->game->plyr_y) * (v_y - val->game->plyr_y)));
// 	if (sqrt((h_x - val->game->plyr_x) * (h_x - val->game->plyr_x) + (h_y - val->game->plyr_y) * (h_y - val->game->plyr_y)) // Pythagorean theorem (must use deltax and deltay)
// 		< sqrt((v_x - val->game->plyr_x) * (v_x - val->game->plyr_x) + (v_y - val->game->plyr_y) * (v_y - val->game->plyr_y))) // Pythagorean theorem is used to get the lenght of a ray
// 	{
// 		draw_line(*val, 1, val->game->plyr_x, val->game->plyr_y, h_x, h_y, 0xff00ff);
// 		return (sqrt((h_x - val->game->plyr_x) * (h_x - val->game->plyr_x) + (h_y - val->game->plyr_y) * (h_y - val->game->plyr_y)));
// 	}
// 	draw_line(*val, 1, val->game->plyr_x, val->game->plyr_y, v_x, v_y, 0xff00ff);
// 	return (sqrt((v_x - val->game->plyr_x) * (v_x - val->game->plyr_x) + (v_y - val->game->plyr_y) * (v_y - val->game->plyr_y)));
// }

// void	draw_rays(t_val *val)
// {
// 	float	angle;
// 	int		i;

// 	angle = limit_angle(val->game->plyr_dir + FOV /2);
// 	i = 0;
// 	while (i < RAYS)
// 	{
// 		printf("ray direction: %f PI\n", angle / PI);
// 		val->rays[i] = draw_one_ray(val, angle);
// 		angle = limit_angle(angle - FOV / (RAYS -1));
// 		i++;
// 	}
// 	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
// }
////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// third method (please work)

// void	draw_line(t_val val, int endX, int endY, int color)
// {
// 	double	deltaX = (endX - val.game->plyr_x) /10;
// 	double	deltaY = (endY - val.game->plyr_y) /10;

// 	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
// 	deltaX /= pixels;
// 	deltaY /= pixels;

// 	double	pixelX = val.game->plyr_x /10;
// 	double	pixelY = val.game->plyr_y /10;
	
// 	while (pixels)
// 	{
// 		color_map_pixel(val, round(pixelX), round(pixelY), color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		pixels--;
// 	}
	
// }

// void	horizontal_hit(t_val *val, float angle, int *hx, int *hy)
// {
// 	*hx = val->game->plyr_x;
// 	*hy = val->game->plyr_y;
// 	// if (angle > EPSILON && angle < PI - EPSILON)
// 	if (angle >= 0 && angle <= PI)
// 	{
// 		while (inside_empty_space(*val, *hx, *hy) && *hx >= 0) // to be tested: Player position: x: 137, y: 79, direction: 1.450000 PI
// 		{
// 			*hy -= TILE;
// 			*hx = val->game->plyr_x + (val->game->plyr_y - *hy) / tan(angle); 
// 		}
// 		// printf("hx: %d, hy: %d\n", *hx, *hy);
// 		if (*hx < 0 || *hx >= val->game->map_x)
// 		{
// 			*hx = val->game->map_x;
// 			*hy = val->game->map_y;
// 			return ;
// 		}
// 		while (!inside_empty_space(*val, *hx, *hy) || *hx < 0)
// 		{
// 			(*hy)++;
// 			*hx = val->game->plyr_x + (val->game->plyr_y - *hy) / tan(angle); 
// 		}
// 	}
// 	else
// 	{
// 		while (inside_empty_space(*val, *hx, *hy) && *hx >= 0)
// 		{
// 			*hy += TILE;
// 			*hx = val->game->plyr_x + (val->game->plyr_y - *hy) / tan(angle); 
// 		}
// 		printf("hx: %d, hy: %d\n", *hx, *hy);
// 		if (*hx < 0 || *hx >= val->game->map_x)
// 		{
// 			*hx = val->game->map_x;
// 			*hy = val->game->map_y;
// 			return ;
// 		}
// 		while (!inside_empty_space(*val, *hx, *hy))
// 		{
// 			(*hy)--;
// 			*hx = val->game->plyr_x + (val->game->plyr_y - *hy) / tan(angle); 
// 		}
// 	}
// }

// void	vertical_hit(t_val *val, float angle, int *vx, int *vy)
// {
// 	*vx = val->game->plyr_x;
// 	*vy = val->game->plyr_y;
// 	// if (angle > EPSILON && angle < PI - EPSILON)
// 	if (angle >= 3 * PI / 2 || angle <= PI / 2)
// 	{
// 		while (inside_empty_space(*val, *vx, *vy) && *vy >= 0)
// 		{
// 			*vx += TILE;
// 			*vy = val->game->plyr_y + (val->game->plyr_x - *vx) * tan(angle);
// 		}
// 		// printf("right half: vx: %d, vy: %d\n", *vx, *vy);
// 		if (*vy < 0 || *vy >= val->game->map_y)
// 		{
// 			*vx = val->game->map_x;
// 			*vy = val->game->map_y;
// 			return ;
// 		}
// 		while (!inside_empty_space(*val, *vx, *vy))
// 		{
// 			(*vx)--;
// 			*vy = val->game->plyr_y + (val->game->plyr_x - *vx) * tan(angle);
// 		}
// 	}
// 	else
// 	{
// 		while (inside_empty_space(*val, *vx, *vy) && *vy >= 0)
// 		{
// 			*vx -= TILE;
// 			*vy = val->game->plyr_y + (val->game->plyr_x - *vx) * tan(angle);
// 		}
// 		printf("left half: vx: %d, vy: %d\n", *vx, *vy);
// 		if (*vy < 0 || *vy >= val->game->map_y)
// 		{
// 			*vx = val->game->map_x;
// 			*vy = val->game->map_y;
// 			return ;
// 		}
// 		while (!inside_empty_space(*val, *vx, *vy))
// 		{
			
// 			(*vx)++;
// 			*vy = val->game->plyr_y + (val->game->plyr_x - *vx) * tan(angle);
// 		}
// 	}
// }

// float	draw_one_ray(t_val *val, float angle)
// {
// 	int	hx;
// 	int	hy;
// 	int	vx;
// 	int	vy;

// 	// horizontal_hit(val, angle, &hx, &hy);
// 	// draw_line(*val, hx, hy, 0xff0000); // red
// 	// vertical_hit(val, angle, &vx, &vy);
// 	// draw_line(*val, vx, vy, 0x00ff00); // green

// 	horizontal_hit(val, angle, &hx, &hy);
// 	vertical_hit(val, angle, &vx, &vy);
// 	if (sqrt((hx - val->game->plyr_x) * (hx - val->game->plyr_x) + (hy - val->game->plyr_y) * (hy - val->game->plyr_y))
// 		<  sqrt((vx - val->game->plyr_x) * (vx - val->game->plyr_x) + (vy - val->game->plyr_y) * (vy - val->game->plyr_y)))
// 	{
// 		draw_line(*val, hx, hy, 0xff0000); // red
// 		return (sqrt((hx - val->game->plyr_x) * (hx - val->game->plyr_x) + (hy - val->game->plyr_y) * (hy - val->game->plyr_y)));
// 	}
// 	draw_line(*val, vx, vy, 0x00ff00); // green
// 	return (sqrt((vx - val->game->plyr_x) * (vx - val->game->plyr_x) + (vy - val->game->plyr_y) * (vy - val->game->plyr_y)));
// }

// void	draw_rays(t_val *val)
// {
// 	float	angle;
// 	int		i;

// 	angle = limit_angle(val->game->plyr_dir + FOV /2);
// 	// angle = val->game->plyr_dir;
// 	i = 0;
// 	while (i < RAYS)
// 	{
// 		printf("ray direction: %f PI\n", angle / PI);
// 		val->rays[i] = draw_one_ray(val, angle);
// 		angle = limit_angle(angle - FOV / (float)(RAYS -1));
// 		i++;
// 	}
// 	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
// }
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// fourth method of ray casting
void	draw_line(t_val val, int endX, int endY, int color)
{
	// double	deltaX = endX - val.game->plyr_x;
	// double	deltaY = endY - val.game->plyr_y;
	// printf("draw_line end point: x: %d, y: %d\n", endX, endY);
	double	deltaX = (endX - val.game->plyr_x) /2;
	double	deltaY = (endY - val.game->plyr_y) /2;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;

	// double	pixelX = val.game->plyr_x;
	// double	pixelY = val.game->plyr_y;
	double	pixelX = val.game->plyr_x /2;
	double	pixelY = val.game->plyr_y /2;
	
	while (pixels)
	{
		color_map_pixel(val, round(pixelX), round(pixelY), color);
		pixelX += deltaX;
		pixelY += deltaY;
		pixels--;
	}
	
}

float	vertical_cast(t_val val, float angle, int ray_number)
{
	float	x;
	float	y;
	float	t;

	// protect infinity
	// if ((angle <= PI / 2 + EPSILON && angle >= PI / 2 - EPSILON) || (angle <= 3 * PI / 2 + EPSILON && angle >= 3 * PI / 2 - EPSILON))
	if (angle == PI / 2.0 || angle == 3.0 * PI / 2.0)
		return (424242424);
	t = -tan(angle);
	if (angle < PI / 2 || angle > 3 * PI / 2)
	{
		x = val.game->plyr_x + TILE - val.game->plyr_x % TILE;
		y = val.game->plyr_y + (x - val.game->plyr_x) * t;
		while (inside_empty_space(val, x, y))
		{
			x += TILE;
			y = val.game->plyr_y + (x - val.game->plyr_x) * t;
		}
		// x--;
		// y = val.game->plyr_y + (x - val.game->plyr_x) * t;
	}
	else
	{
		x = val.game->plyr_x - val.game->plyr_x % TILE -1;
		y = val.game->plyr_y + (x - val.game->plyr_x) * t;
		while (inside_empty_space(val, x, y))
		{
			x -= TILE;
			y = val.game->plyr_y + (x - val.game->plyr_x) * t;
		}
		// x++;
		// y = val.game->plyr_y + (x - val.game->plyr_x) * t;
	}
	// if (ray_number >= 590 && ray_number <= 600)
	// 	printf("vertical: x: %f, y: %f\n", x, y);
	// printf("x: %f, y: %f\n", x, y);
	// draw_line(val, round(x), round(y), 0xff0000);
	return (sqrt((val.game->plyr_x - x) * (val.game->plyr_x - x)
		+ (val.game->plyr_y - y) * (val.game->plyr_y - y)));
}

float	horizontal_cast(t_val val, float angle, int ray_number)
{
	float	x;
	float	y;
	float	t;

	// if ((angle <= EPSILON || angle >= 2 * PI - EPSILON) || (angle <= PI + EPSILON && angle >= PI - EPSILON))
	if (angle == 0.0 || angle == 2.0 * PI || angle == PI)
		return (424242424);
	t = - 1 / tan(angle);
	// protect infinity
	if (angle < PI)
	{
		y = val.game->plyr_y - val.game->plyr_y % TILE -1;
		x = val.game->plyr_x + (y - val.game->plyr_y) * t;
		while (inside_empty_space(val, x, y))
		{
			y -= TILE;
			x = val.game->plyr_x + (y - val.game->plyr_y) * t;
		}
		// y += TILE;
		// x = val.game->plyr_x + (y - val.game->plyr_y) * t;
		// draw_line(val, x, y, 0x00ffff);
		// printf("here\n");
	}
	else
	{
		y = val.game->plyr_y + TILE - val.game->plyr_y % TILE;
		x = val.game->plyr_x + (y - val.game->plyr_y) * t;
		while (inside_empty_space(val, x, y))
		{
			y += TILE;
			x = val.game->plyr_x + (y - val.game->plyr_y) * t;
		}
		// y--;
		// x = val.game->plyr_x + (y - val.game->plyr_y) * t;
	}
	// if (ray_number >= 590 && ray_number <= 600)
	// 	printf("horizontal: x: %f, y: %f\n", x, y);
	// printf("x: %f, y: %f\n", x, y);
	// draw_line(val, round(x), round(y), 0xff0000);
	return (sqrt((val.game->plyr_x - x) * (val.game->plyr_x - x)
		+ (val.game->plyr_y - y) * (val.game->plyr_y - y)));
}

float	cast_ray(t_val val, float *x, float *y, float angle, int ray_number)
{
	float	h_len;
	float	v_len;

	h_len = horizontal_cast(val, angle, ray_number);
	v_len = vertical_cast(val, angle, ray_number);
	// if (ray_number >= 590 && ray_number <= 600)
	// 	printf("ray_number: %d, h_len: %f, v_len: %f at angle %f PI\n", ray_number, h_len, v_len, angle / PI);
	if (h_len < v_len)
	{
		*x = val.game->plyr_x + cos(angle) * h_len;
		*y = val.game->plyr_y - sin(angle) * h_len;
		return (h_len);
	}
	// printf("vertical is chosen in ray %d\n", ray_number);
	*x = val.game->plyr_x + cos(angle) * v_len;
	*y = val.game->plyr_y - sin(angle) * v_len;
	return (v_len);
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

	angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (i < val->width)
	{
		val->rays[i] = cast_ray(*val, &x, &y, angle, i);
		// printf("final %d: x: %f, y: %f\n", i, round(x), round(y));
		draw_line(*val, round(x), round(y), 0xff0000);
		i++;
		angle = limit_angle(angle - FOV / (float)(val->width -1));
	}
}
///////////////////////////////////////////////////////////////////////////////////////