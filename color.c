/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:36:21 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/06 16:54:47 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_fetched(t_val *val, t_ray ray, double y, double wall_height)
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

void	color_map_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	offset = y * val.map_data.sline + x * (val.map_data.bpp / 8);
	*(int *)(val.map_data.img_data + offset) = color;
}

void	color_game_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	if (color < 0)
		return ;
	offset = y * val.data.sline + x * (val.data.bpp / 8);
	*(int *)(val.data.img_data + offset) = color;
}
