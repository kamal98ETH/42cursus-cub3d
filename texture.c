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

void	ft_open_textures(t_val *val)
{
	t_game	*map;

	map = val->game;
	map->ea.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->ea.path, &(map->ea.width), &(map->ea.height));
	map->no.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->no.path, &(map->no.width), &(map->no.height));
	map->so.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->so.path, &(map->so.width), &(map->so.height));
	map->we.img.img = mlx_xpm_file_to_image(val->mlx_ptr, map->we.path, &(map->we.width), &(map->we.height));
	if (!map->ea.img.img || !map->no.img.img || !map->so.img.img || !map->we.img.img)
	{
		printf("\e[31m>> [TEXTURE ERORR] can't open file!\e[0m \n");
		exit(1);
	}
	map->ea.img.img_data = mlx_get_data_addr(map->ea.img.img, &(map->ea.img.bpp), &(map->ea.img.sline), &(map->ea.img.endian));
    map->no.img.img_data = mlx_get_data_addr(map->no.img.img, &(map->no.img.bpp), &(map->no.img.sline), &(map->no.img.endian));
    map->so.img.img_data = mlx_get_data_addr(map->so.img.img, &(map->so.img.bpp), &(map->so.img.sline), &(map->so.img.endian));
    map->we.img.img_data = mlx_get_data_addr(map->we.img.img, &(map->we.img.bpp), &(map->we.img.sline), &(map->we.img.endian));

    map->ea.img.px = (int *)map->ea.img.img_data;
    map->no.img.px = (int *)map->no.img.img_data;
    map->so.img.px = (int *)map->so.img.img_data;
    map->we.img.px = (int *)map->we.img.img_data;
    printf("\e[32m>> [TEXTURE] textures loaded successfully!\e[0m \n");
}
