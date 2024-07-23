/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/23 19:03:37 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_val *val)
{
	float	wall_height;
	float	y_top;
	int y;
	int	x;
	float	ray_angle;
	t_ray	ray;

	x = 0;
	ray_angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (x < val->width)
	{
		cast_ray(*val, &ray, ray_angle);
		wall_height = ray.dist;
		wall_height *= cos(limit_angle(val->game->plyr_dir - ray_angle));
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
					color_game_pixel(*val, x, y, 0xff0000);
				if (ray.dir == 'S') // hitting south
					color_game_pixel(*val, x, y, 0x00ff00);
				if (ray.dir == 'E') // hitting east
					color_game_pixel(*val, x, y, 0x0000ff);
				if (ray.dir == 'W') // hitting west
					color_game_pixel(*val, x, y, 0xff00ff);
			}
			else if (y < y_top) // ceiling
				color_game_pixel(*val, x, y, 0x87ceeb);
			else // floor
				color_game_pixel(*val, x, y, 0x543b0e);
			y++;
		}
		ray_angle = limit_angle(ray_angle - FOV / (float)(val->width));
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

void	render(t_val *val)
{
	draw_map(val);
	// draw_rays(val);
	// for debugging
	printf("Player position: x: %f, y: %f, direction: %f PI\n", val->game->plyr_x, val->game->plyr_y, val->game->plyr_dir / PI);
	
	// for (int i = 0; i < RAYS; i++)
	// 	printf("%f, ", val->rays[i]);
	// printf("\n\n\n");
	draw_walls(val);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
}
