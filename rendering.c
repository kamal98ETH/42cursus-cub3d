/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/21 18:30:04 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_fetched(t_val *val, t_ray ray, float y, float wall_height)
{
	if (ray.dir == 'N')
		return (txtr_fetch(&val->game->no, ray, y, wall_height));
	if (ray.dir == 'S')
		return (txtr_fetch(&val->game->so, ray, y, wall_height));
	if (ray.dir == 'E')
		return (txtr_fetch(&val->game->ea, ray, y, wall_height));
	if (ray.dir == 'W')
		return (txtr_fetch(&val->game->we, ray, y, wall_height));
	if (ray.dir == 'D')
		return (0x004c7f);
	if (ray.dir == 'd')
		return (0xbae3ff);
}

void	cast_and_draw(t_val *val, int x, float ray_angle)
{
	int		y;
	float	wall_height;
	float	y_top;
	t_ray	ray;

	cast_ray(*val, &ray, ray_angle);
	wall_height = ray.dist * cos(val->game->plyr_dir - ray_angle);
	wall_height = (TILE * val->height) / wall_height;
	y_top = (val->height / 2) - (wall_height / 2);
	y = 0;
	while (y < val->height)
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
	float	ray_angle;

	x = 0;
	ray_angle = val->game->plyr_dir + FOV / 2;
	while (x < val->width)
	{
		cast_and_draw(val, x, ray_angle);
		ray_angle = ray_angle - FOV / (float)(val->width);
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

// for debugging
	// printf("Player position: x: %f, y: %f, direction: %f PI\n",
	// val->game->plyr_x, val->game->plyr_y, val->game->plyr_dir / PI);
int	render(t_val *val)
{
	float	tmpx;
	float	tmpy;
	float	tmpd;
	t_game	*game;

	game = val->game;
	tmpx = game->plyr_x;
	tmpy = game->plyr_y;
	tmpd = game->plyr_dir;
	move_player(val);
	if (game->plyr_x != tmpx || game->plyr_y != tmpy || game->plyr_dir != tmpd)
	{
		draw_walls(val);
		draw_map(val);
	}
	else if (val->start)
	{
		draw_walls(val);
		draw_map(val);
		val->start = 0;
	}
	return (0);
}
