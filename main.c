/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/24 01:27:49 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_val	*val;

	if (ac != 2)
		return (printf("usage:\n\t./cub3d <map filename>\n"), 1);
	val = (t_val *)malloc(sizeof(t_val));
	if (!val)
		return (1);
	val->game = parsing(av[1]);
	if (!val->game)
		return (free(val), 1);
	val->height = 800;
	val->width = 1000;
	val->start = 1;

	//to be deleted
	// printf("map x: %d, map y: %d\n", val->game->map_x, val->game->map_y);
	// val->game->plyr_x = 1244.980347;
	// val->game->plyr_y = 2805.075684;
	// val->game->plyr_dir = 1.372170 * PI;

	int i = 0;
	while (i < 6)
		val->keys[i++] = 0;

	if (!val->game->map)
	{
		free(val->game);
		free(val);
		return (1);
	}
	val->mlx_ptr = mlx_init(); // check if these fail
	val->win_ptr = mlx_new_window(val->mlx_ptr, val->width, val->height, "cub3D");
	val->img_ptr = mlx_new_image(val->mlx_ptr, val->width, val->height);
	val->data.img_data = mlx_get_data_addr(val->img_ptr, &(val->data.bpp), &(val->data.sline), &(val->data.endian));
	val->img_map_ptr = mlx_new_image(val->mlx_ptr, MINIMAP_X, MINIMAP_Y);
	val->map_data.img_data = mlx_get_data_addr(val->img_map_ptr, &(val->map_data.bpp), &(val->map_data.sline), &(val->map_data.endian));
	
	ft_open_textures(val);
	
	door_init(val);
	mlx_hooks(val);
	mlx_loop_hook(val->mlx_ptr, render, val);
	
	mlx_mouse_get_pos(val->mlx_ptr, val->win_ptr, &(val->tmpx), &(val->tmpy));
	// printf("player init coordinates: x: %f, y: %f\n", val->game->plyr_x, val->game->plyr_y);
	

	mlx_loop(val->mlx_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_map_ptr);
	mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free_map(val->game);
	free(val->mlx_ptr);
	clean_doors(val->game->doors);
	free(val);
	return (0);
}
