/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:33:19 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/06 11:46:20 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	txtr_fetch(t_texture *txtr, t_ray ray, double y_off, double wall_height)
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

void	get_txt(t_texture *txt, t_val *val)
{
	txt->img.img = mlx_xpm_file_to_image(val->mlx_ptr, txt->path, \
		&(txt->width), &(txt->height));
	if (txt->img.img)
		return ;
	printf(">> [TEXTURE ERORR] can't open file: <%s>\n", txt->path);
	ft_clean(val);
	exit(1);
}

void	set_txt(t_data *img)
{
	img->img_data = mlx_get_data_addr(img->img, \
		&(img->bpp), &(img->sline), &(img->endian));
}

void	ft_open_textures(t_val *val)
{
	t_game	*map;

	map = val->game;
	get_txt(&(map->ea), val);
	get_txt(&(map->no), val);
	get_txt(&(map->so), val);
	get_txt(&(map->we), val);
	get_txt(&(map->dr), val);
	get_txt(&(map->df), val);
	get_txt(&(map->en), val);
	set_txt(&(map->ea.img));
	set_txt(&(map->no.img));
	set_txt(&(map->so.img));
	set_txt(&(map->we.img));
	set_txt(&(map->dr.img));
	set_txt(&(map->df.img));
	set_txt(&(map->en.img));
	printf("\e[32m>> [TEXTURE] textures loaded successfully!\e[0m \n");
}
