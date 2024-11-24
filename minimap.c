/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:30:28 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/24 02:34:37 by laoubaid         ###   ########.fr       */
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

void	color_mini_horizontal_line(t_val *val, int *x, int y, int mini_y)
{
	int	mini_x;
	int	scale;

	scale = get_scale(val->game->map_x, val->game->map_y);
	mini_x = 0;
	while (mini_x < MINIMAP_X)
	{
		if (mini_x <= 2 || mini_x >= MINIMAP_X -2
			|| mini_y <= 2 || mini_y >= MINIMAP_Y -2)
			color_map_pixel(*val, mini_x, mini_y, 0xffffff);
		else if (*x < 0 || y < 0 || *x >= val->game->map_x
			|| y >= val->game->map_y || corresponding_tile(*val, *x, y) == ' ')
			color_map_pixel(*val, mini_x, mini_y, 0xcccccc);
		else if (mini_x >= MINIMAP_X / 2 - 2 && mini_x <= MINIMAP_X / 2 + 2
			&& mini_y >= MINIMAP_Y / 2 - 2 && mini_y <= MINIMAP_Y / 2 + 2)
			color_map_pixel(*val, mini_x, mini_y, 0xff0000);
		else if (empty_space(*val, *x, y) == 1)
			color_map_pixel(*val, mini_x, mini_y, 0x0);
		else if (empty_space(*val, *x, y) == 2)
			color_map_pixel(*val, mini_x, mini_y, 0xfbc21a);
		else
			color_map_pixel(*val, mini_x, mini_y, 0xffffff);
		mini_x++;
		*x += scale;
	}
}

void	draw_map_from_center(t_val *val, int x, int y)
{
	int	mini_y;
	int	scale;

	mini_y = 0;
	scale = get_scale(val->game->map_x, val->game->map_y);
	x -= scale * MINIMAP_X / 2;
	y -= scale * MINIMAP_Y / 2;
	while (mini_y < MINIMAP_Y)
	{
		color_mini_horizontal_line(val, &x, y, mini_y);
		x -= scale * MINIMAP_X;
		y += scale;
		mini_y++;
	}
}

void	draw_map(t_val *val)
{
	draw_map_from_center(val, val->game->plyr_x, val->game->plyr_y);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr,
		val->img_map_ptr, 10, val->height -10 - MINIMAP_Y);
}
