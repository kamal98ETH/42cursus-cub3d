/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/10/31 02:36:47 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int getx(t_ray ray, int width)
{
	if (ray.dir == 'E' || ray.dir == 'W')
		return ((width / TILE) * ray.y);
	else
		return ((width / TILE) * ray.x);
}

void	draw_walls(t_val *val)
{
	float	wall_height;
	float	y_top;
	int		y;
	int		x;
	float	ray_angle;
	t_ray	ray;

	x = 0;
	ray_angle = val->game->plyr_dir + FOV /2;
	while (x < val->width)
	{
		cast_ray(*val, &ray, ray_angle);
		wall_height = ray.dist;
		wall_height *= cos(val->game->plyr_dir - ray_angle);
		wall_height = (30 * val->height) / wall_height;
		if (wall_height > val->height)
			wall_height = val->height;
		y_top = (val->height / 2) - (wall_height / 2);
		y = 0;
		while (y < val->height)
		{
			if (y < y_top + wall_height && y > y_top) // wall
			{
				if (ray.dir == 'N') // hitting north side of wall
					color_game_pixel(*val, x, y, get_texture_px_color(&val->game->no, getx(ray, val->game->no.width), y - y_top, wall_height));
				if (ray.dir == 'S') // hitting south
					color_game_pixel(*val, x, y, get_texture_px_color(&val->game->so, getx(ray, val->game->so.width), y - y_top, wall_height));
				if (ray.dir == 'E') // hitting east
					color_game_pixel(*val, x, y, get_texture_px_color(&val->game->ea, getx(ray, val->game->ea.width), y - y_top, wall_height));
				if (ray.dir == 'W') // hitting west
					color_game_pixel(*val, x, y, get_texture_px_color(&val->game->we, getx(ray, val->game->we.width), y - y_top, wall_height));
			}
			else if (y < y_top) // ceiling
				color_game_pixel(*val, x, y, val->game->ccol.hexacode);
			else // floor
				color_game_pixel(*val, x, y, val->game->fcol.hexacode);
			y++;
		}
		ray_angle = ray_angle - FOV / (float)(val->width);
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

int	render(t_val *val)
{
	// printf("rendring...\n");
	move_player(val);
	draw_walls(val);
	draw_map(val);
}
