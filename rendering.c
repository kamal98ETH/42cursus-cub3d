/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/18 00:17:25 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_walls(t_val *val)
{
	// int	*rays;
	float	wall_height;
	int y_top;
	int y;
	int	x;
	float	ray_angle;

	// draw_rays(val);
	x = 0;
	ray_angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (x < RAYS)
	{
		// printf("val->rays[%d] before is: %f\n", x, val->rays[x]);
		
		// val->rays[x] = round(val->rays[x]);
		// if (x == 150 || x == 190 || x == 200 || x == 240)
			// printf("val->rays[%d] before cos: %f, angle: %f PI\n", x, val->rays[x], ray_angle / PI);
		val->rays[x] *= cos(limit_angle(- ray_angle + val->game->plyr_dir));
		// if (x == 150 || x == 190 || x == 200 || x == 240)
		// 	printf("val->rays[%d] after cos: %f, angle: %f PI\n", x, val->rays[x], ray_angle / PI);
		// printf("ray: %d => %f\n", x, val->rays[x]);

		// printf("val->rays[%d] after is: %f\n", x, val->rays[x]);
		// wall_height = 10.0 * ((float)val->height / val->rays[x]);
		wall_height = (TILE / val->rays[x]) * ((val->width / 2) / tan(FOV / 2));
		// wall_height = 2 * val->rays[x] / tan(FOV / 2);
		// wall_height = 10 *  val->height / val->rays[x];
		
		// printf("wall height is: %f\n", wall_height);
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

	// smaller amount of rays
	// int	z = 0;
	// float	l_wall_height;
	// float	r_wall_height;
	// while (x < val->width)
	// {
	// 	z = 0;
	// 	l_wall_height = val->rays[x / 10];
	// 	r_wall_height = val->rays[x / 10 +1];
	// 	while (z < 10)
	// 	{
	// 		wall_height = l_wall_height + z * (r_wall_height - l_wall_height) / 10;
	// 		wall_height *= cos(limit_angle(- ray_angle + val->game->plyr_dir));
	// 		wall_height = (20 /wall_height) * ((val->width / 2) / tan(FOV / 2));
	// 		y_top = round((val->height / 2) - (wall_height / 2));
	// 		y = 0;
	// 		while (y < val->height)
	// 		{
	// 			if (y < y_top + round(wall_height) && y > y_top)
	// 				color_game_pixel(*val, x, y, 0xe5d9d2);
	// 			else if (y < y_top)
	// 				color_game_pixel(*val, x, y, 0x87ceeb);
	// 			else
	// 				color_game_pixel(*val, x, y, 0x543b0e);
	// 			y++;
	// 		}
	// 		z++;
	// 		x++;
	// 	}
	// 	ray_angle = limit_angle(ray_angle - FOV / RAYS);
	// }

	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

void	render(t_val *val)
{
	// draw_line(*val, 0, 100, 100, 300, 300, 0xffffff);
	// draw_line(*val, 0, 300, 200, 600, 200, 0xffffff);
	// mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
	draw_map(val);
	draw_rays(val);
	// val->rays[0] = draw_one_ray(val, val->game->plyr_dir);
	
	// for debugging
	printf("Player position: x: %d, y: %d, direction: %f PI\n", val->game->plyr_x, val->game->plyr_y, val->game->plyr_dir / PI);
	
	// for (int i = 0; i < RAYS; i++)
	// 	printf("%f, ", val->rays[i]);
	// printf("\n\n\n");
	draw_walls(val);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
}
