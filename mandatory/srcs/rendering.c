/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/20 18:32:15 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_and_draw(t_val *val, int x, double ray_angle)
{
	int		y;
	double	wall_height;
	double	y_top;
	t_ray	ray;

	cast_ray(*val, &ray, ray_angle);
	wall_height = ray.dist * cos(val->game->plyr_dir - ray_angle);
	if (wall_height != 0)
		wall_height = (TILE * HEIGHT) / wall_height;
	y_top = (HEIGHT / 2) - (wall_height / 2);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < y_top + wall_height && y > y_top)
			color_game_pixel(*val, x, y,
				color_fetched(val, ray, y - y_top, wall_height));
		else if (y < y_top)
			color_game_pixel(*val, x, y, val->game->ccol.hexacode);
		else
			color_game_pixel(*val, x, y, val->game->fcol.hexacode);
		y++;
	}
}

void	draw_walls(t_val *val)
{
	int		x;
	double	angle_diff;
	double	ray_angle;

	x = 0;
	ray_angle = val->game->plyr_dir + FOV / 2;
	angle_diff = FOV / (double)(WIDTH);
	while (x < WIDTH)
	{
		cast_and_draw(val, x, ray_angle);
		ray_angle = ray_angle - angle_diff;
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

int	render(t_val *val)
{
	move_player(val);
	draw_walls(val);
	return (0);
}
