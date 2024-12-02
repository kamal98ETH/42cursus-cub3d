/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:33:48 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/02 23:02:04 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_fetched(t_val *val, t_ray ray, float y, float wall_height)
{
	if (ray.door == 'D')
		return (txtr_fetch(&val->game->dr, ray, y, wall_height));
	if (ray.door == 'd')
		return (txtr_fetch(&val->game->df, ray, y, wall_height));
	if (ray.dir == 'N')
		return (txtr_fetch(&val->game->no, ray, y, wall_height));
	if (ray.dir == 'S')
		return (txtr_fetch(&val->game->so, ray, y, wall_height));
	if (ray.dir == 'E')
		return (txtr_fetch(&val->game->ea, ray, y, wall_height));
	if (ray.dir == 'W')
		return (txtr_fetch(&val->game->we, ray, y, wall_height));
}

void	cast_and_draw(t_val *val, int x, float ray_angle)
{
	int		y;
	float	wall_height;
	float	y_top;
	t_ray	ray;

	cast_ray(*val, &ray, ray_angle);
	wall_height = ray.dist * cos(val->game->plyr_dir - ray_angle);
	if (wall_height != 0)
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

int enemy_texture_fetch(t_texture *txtr, int x, int y, int tile)
{
	int x_off;
	int y_off;
	int	offset;

	x_off = x * txtr->width / tile;
	y_off = y * txtr->height / tile;
	offset = (int)y_off * txtr->width + x_off;
	return (*(((int *)txtr->img.img_data) + offset));
}

int check_if_invincible(float angle_diff)
{
	if (angle_diff < 0)
		angle_diff = angle_diff * -1;
	if (angle_diff < FOV / 2)
		return (0);
	return (1);
}

void	draw_enemy(t_val *val)
{
	int tile = 0;
	int x_start = 0;
	int y_start = 0;
	int i = 0;
	int j = 0;
	float angle = 0;
	t_ray ray;

	cast_ray(*val, &ray, val->game->enemy_dir);
	angle = val->game->plyr_dir - val->game->enemy_dir;
	if (ray.dist < val->game->dist * TILE || check_if_invincible(angle))
		return ;
	tile = (val->height) / val->game->dist;
	x_start = val->width / 2 - tile / 2 + (val->width / 2) * (angle / (FOV / 2)) - tile / 2;
	y_start = val->height / 2 - tile / 2;
	i = x_start;
	while (i < x_start + tile) 
	{
		j = y_start;
		while (j < y_start + tile)
		{
			color_game_pixel(*val, i, j, enemy_texture_fetch(&val->game->en, i - x_start, j - y_start, tile));
			j++;
		}
		i++;
	}
}

void	calculate_enemy_direction(t_val *val)
{
	float dx;
	float dy;

	dx = val->game->enemy_x - val->game->plyr_x;
	dy = val->game->enemy_y - val->game->plyr_y;
	val->game->enemy_dir = -(float)atan2(dy, dx);
	val->game->enemy_dir = limit_angle(val->game->enemy_dir);
}

void	move_enemy(t_val *val)
{
	float dx;
	float dy;
	float dist = 0;
	float angle = 0;

	dx = val->game->enemy_x;
	dy = val->game->enemy_y;
	dist = sqrt(pow(val->game->enemy_x - val->game->plyr_x, 2) + pow(val->game->enemy_y - val->game->plyr_y, 2)) / TILE;
	calculate_enemy_direction(val);
	val->game->dist = dist;
	angle = val->game->enemy_dir + PI;
	angle = limit_angle(angle);
	dx = (val->game->plyr_x - val->game->enemy_x) * (ENYSPEED / (dist * TILE));
	dy = (val->game->plyr_y - val->game->enemy_y) * (ENYSPEED / (dist * TILE));
	val->game->enemy_x += dx;
	val->game->enemy_y += dy;
}

int	render(t_val *val)
{
	move_player(val);
	move_enemy(val);
	check_death(val);
	draw_walls(val);
	draw_enemy(val);
	draw_map(val);
	return (0);
}
