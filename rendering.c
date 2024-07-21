/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/21 01:57:53 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_val *val)
{
	float	wall_height;
	int y_top;
	int y;
	int	x;
	float	ray_angle;

	x = 0;
	ray_angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (x < RAYS)
	{
		
		val->rays[x] *= cos(limit_angle(- ray_angle + val->game->plyr_dir));
		wall_height = (TILE / val->rays[x]) * ((val->width / 2) / tan(FOV / 2));
		y_top = floor((val->height / 2.0) - (wall_height / 2.0));
		y = 0;
		while (y < val->height)
		{
			if (y < y_top + round(wall_height) && y > y_top)
				color_game_pixel(*val, x, y, 0xe5d9d2);
			else if (y < y_top)
				color_game_pixel(*val, x, y, 0x87ceeb);
			else
				color_game_pixel(*val, x, y, 0x543b0e);
			y++;
		}
		ray_angle = limit_angle(ray_angle - FOV / (float)(RAYS -1));
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

void	render(t_val *val)
{
	draw_map(val);
	draw_rays(val);
	// for debugging
	// printf("Player position: x: %f, y: %f, direction: %f PI\n", val->game->plyr_x, val->game->plyr_y, val->game->plyr_dir / PI);
	
	// for (int i = 0; i < RAYS; i++)
	// 	printf("%f, ", val->rays[i]);
	// printf("\n\n\n");

	draw_walls(val);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
}
