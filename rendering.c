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

void	draw_walls(t_val *val)
{
	float	wall_height;
	float	save_h;
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
		save_h = wall_height;  // to fix the wall height problem when it surpasses window height later
		if (wall_height > val->height)
			wall_height = val->height;
		y_top = (val->height / 2) - (wall_height / 2);
		y = 0;
		while (y < val->height)
		{
			if (y < y_top + wall_height && y > y_top) // wall
			{
				if (ray.dir == 'N')
					color_game_pixel(*val, x, y, txtr_fetch(&val->game->no, ray, y - y_top, wall_height));
				if (ray.dir == 'S')
					color_game_pixel(*val, x, y, txtr_fetch(&val->game->so, ray, y - y_top, wall_height));
				if (ray.dir == 'E')
					color_game_pixel(*val, x, y, txtr_fetch(&val->game->ea, ray, y - y_top, wall_height));
				if (ray.dir == 'W')
					color_game_pixel(*val, x, y, txtr_fetch(&val->game->we, ray, y - y_top, wall_height));
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
