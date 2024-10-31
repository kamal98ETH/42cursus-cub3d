/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:30:28 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/10/30 02:18:43 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// hard coded map dimentions
int	map_width = 200;
int	map_height = 150;

void	draw_map_from_center(t_val *val, int x, int y)
{
	int	mini_x = 0;
	int	mini_y = 0;

	x -= MSCALE * map_width / 2;
	y -= MSCALE * map_height / 2;
	while (mini_y < map_height)
	{
		mini_x = 0;
		while (mini_x < map_width)
		{
			if (mini_x <= 2 || mini_x >= map_width -2 || mini_y <= 2 || mini_y >= map_height -2) // borders
				color_map_pixel(*val, mini_x, mini_y, 0xffffff);
			else if (x < 0 || y < 0 || x > 20 * 40 || y > 20 * 40) // coordinates outside the map (hard coded)
				color_map_pixel(*val, mini_x, mini_y, 0xcccccc);
			else if (x >= val->game->plyr_x - 2 * MSCALE && x <= val->game->plyr_x + 2 * MSCALE
					&& y >= val->game->plyr_y - 2 * MSCALE && y <= val->game->plyr_y + 2 * MSCALE)
				color_map_pixel(*val, mini_x, mini_y, 0xff0000);
			else if (inside_empty_space(*val, x, y))
				color_map_pixel(*val, mini_x, mini_y, 0x0);
			else
				color_map_pixel(*val, mini_x, mini_y, 0xffffff);
			mini_x++;
			x += MSCALE;
		}
		x -= MSCALE * map_width;
		y += MSCALE;
		mini_y++;
	}
}

void	draw_map(t_val *val)
{
	draw_map_from_center(val, val->game->plyr_x, val->game->plyr_y);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 10, val->height -10 - map_height);
}
