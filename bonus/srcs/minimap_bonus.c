/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:30:28 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 17:46:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	color_mini_horizontal_line(t_val *val, int *x, int y, int mini_y)
{
	int	mini_x;

	mini_x = 0;
	while (mini_x < MINIMAP_X)
	{
		if (mini_x <= 2 || mini_x >= MINIMAP_X -2 \
			|| mini_y <= 2 || mini_y >= MINIMAP_Y -2 \
			|| corresponding_tile(*val, *x, y) == '1')
			color_map_pixel(*val, mini_x, mini_y, 0xffffff);
		else if (*x < 0 || y < 0 \
			|| *x >= val->game->map_x * TILE \
			|| y >= val->game->map_y * TILE \
			|| corresponding_tile(*val, *x, y) == ' ')
			color_map_pixel(*val, mini_x, mini_y, 0xcccccc);
		else if (empty_space(*val, *x, y) == 2)
			color_map_pixel(*val, mini_x, mini_y, 0xfbc21a);
		mini_x++;
		*x += MSCALE;
	}
}

void	draw_map(t_val *val)
{
	int	x;
	int	y;
	int	mini_y;

	mini_y = 0;
	x = val->game->plyr_x - MSCALE * MINIMAP_X / 2;
	y = val->game->plyr_y - MSCALE * MINIMAP_Y / 2;
	while (mini_y < MINIMAP_Y)
	{
		color_mini_horizontal_line(val, &x, y, mini_y);
		x -= MSCALE * MINIMAP_X;
		y += MSCALE;
		mini_y++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, \
			val->img_map_ptr, 10, HEIGHT -10 - MINIMAP_Y);
}
