/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:30:28 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/10 02:04:24 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_scale(int map_x, int map_y)
{
	if (map_x > map_y)
		return (map_x / MINIMAP_X);
	else
		return (map_y / MINIMAP_Y);
}

void	draw_map_from_center(t_val *val, int x, int y)
{
	int	mini_x = 0;
	int	mini_y = 0;
	int	scale;

	scale = get_scale(val->game->map_x, val->game->map_y);
	x -= scale * MINIMAP_X / 2;
	y -= scale * MINIMAP_Y / 2;
	while (mini_y < MINIMAP_Y)
	{
		mini_x = 0;
		while (mini_x < MINIMAP_X)
		{
			if (mini_x <= 2 || mini_x >= MINIMAP_X -2 || mini_y <= 2 || mini_y >= MINIMAP_Y -2) // borders
				color_map_pixel(*val, mini_x, mini_y, 0xffffff);
			else if (x < 0 || y < 0 || x >= val->game->map_x || y >= val->game->map_y || corresponding_tile(*val, x, y) == 2) // coordinates outside the map (hard coded)
				color_map_pixel(*val, mini_x, mini_y, 0xcccccc);
			else if (mini_x >= MINIMAP_X / 2 - 2 && mini_x <= MINIMAP_X / 2 + 2
					&& mini_y >= MINIMAP_Y / 2 - 2 && mini_y <= MINIMAP_Y / 2 + 2)
				color_map_pixel(*val, mini_x, mini_y, 0xff0000);
			else if (corresponding_tile(*val, x, y) == 0)
				color_map_pixel(*val, mini_x, mini_y, 0x0);
			else
				color_map_pixel(*val, mini_x, mini_y, 0xffffff);
			mini_x++;
			x += scale;
		}
		x -= scale * MINIMAP_X;
		y += scale;
		mini_y++;
	}
}

void	draw_map(t_val *val)
{
	draw_map_from_center(val, val->game->plyr_x, val->game->plyr_y);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 10, val->height -10 - MINIMAP_Y);
	// mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->game->ea.img.img, 10, val->height -10 - MINIMAP_Y);
}
