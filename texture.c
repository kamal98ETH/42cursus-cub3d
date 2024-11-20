/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:33:19 by laoubaid          #+#    #+#             */
/*   Updated: 2024/11/01 01:54:19 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	txtr_fetch(t_texture *txtr, t_ray ray, float y_off, float wall_height)
{
	int	x_off;
	int	offset;

	if (ray.dir == 'E')
		x_off = (int)ray.y % TILE;
	else if (ray.dir == 'W')
		x_off = TILE - ((int)ray.y % TILE);
	else if (ray.dir == 'N')
		x_off = (int)ray.x % TILE;
	else
		x_off = TILE - ((int)ray.x % TILE);
	x_off = x_off * txtr->width / TILE;
	y_off = y_off * txtr->height / wall_height;
	offset = (int)y_off * txtr->width + x_off;
	return (*(((int *)txtr->img.img_data) + offset));
}

void	check_if_open(t_game map)
{
	if (!map.ea.img.img || !map.no.img.img \
		|| !map.so.img.img || !map.we.img.img)
	{
		printf("\e[31m>> [TEXTURE ERORR] can't open file!\e[0m \n");
		exit(1);
	}
}

void	ft_open_textures(t_val *val)
{
	t_game	*map;

	map = val->game;
	map->ea.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->ea.path, \
		&(map->ea.width), &(map->ea.height));
	map->no.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->no.path, \
		&(map->no.width), &(map->no.height));
	map->so.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->so.path, \
		&(map->so.width), &(map->so.height));
	map->we.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->we.path, \
		&(map->we.width), &(map->we.height));
	check_if_open(*map);
	map->ea.img.img_data = mlx_get_data_addr(map->ea.img.img, \
		&(map->ea.img.bpp), &(map->ea.img.sline), &(map->ea.img.endian));
	map->no.img.img_data = mlx_get_data_addr(map->no.img.img, \
		&(map->no.img.bpp), &(map->no.img.sline), &(map->no.img.endian));
	map->so.img.img_data = mlx_get_data_addr(map->so.img.img, \
		&(map->so.img.bpp), &(map->so.img.sline), &(map->so.img.endian));
	map->we.img.img_data = mlx_get_data_addr(map->we.img.img, \
		&(map->we.img.bpp), &(map->we.img.sline), &(map->we.img.endian));
	printf("\e[32m>> [TEXTURE] textures loaded successfully!\e[0m \n");
}
