/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/08 17:46:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cast_and_draw(t_val *val, int x, double ray_angle)
{
	int		y;
	double	wall_height;
	double	y_top;
	t_ray	ray;

	cast_ray(*val, &ray, ray_angle);
	draw_line(*val, ray.x, ray.y, 0xFFFF00);
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

int	get_angle_diff(t_val *val, double *angle_diff)
{
	double	angle_one;
	double	angle_two;
	t_ray	ray;

	angle_one = val->game->plyr_dir - val->game->enemy_dir;
	cast_ray(*val, &ray, val->game->enemy_dir);
	angle_two = 2 * PI - fabs(angle_one);
	if (angle_one * angle_two > 0)
		angle_two *= -1;
	if (fabs(angle_one) < fabs(angle_two))
		*angle_diff = angle_one;
	else
		*angle_diff = angle_two;
	if (ray.dist < val->game->dist * TILE || *angle_diff > FOV / 2)
		return (1);
	return (0);
}

void	draw_enemy(t_val *val, int tile)
{
	int		i;
	int		j;
	int		x_start;
	int		y_start;
	double	angle;

	y_start = HEIGHT / 2 - tile / 2;
	if (get_angle_diff(val, &angle))
		return ;
	x_start = WIDTH / 2 * (1 + (angle / (FOV / 2))) - tile / 2;
	i = x_start;
	while (i < x_start + tile)
	{
		j = y_start;
		while (j < y_start + tile)
		{
			color_game_pixel(*val, i, j, \
			enemy_texture(&val->game->en, i - x_start, j - y_start, tile));
			j++;
		}
		i++;
	}
}

int	render(t_val *val)
{
	move_player(val);
	move_enemy(val);
	check_death(val);
	ft_bzero(val->map_data.img_data, MINIMAP_X * MINIMAP_Y * 4);
	draw_walls(val);
	draw_enemy(val, HEIGHT / val->game->dist);
	draw_map(val);
	return (0);
}
