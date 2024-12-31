/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/12/31 21:28:53 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_destructor(void *mlx_ptr, void *img_ptr)
{
	if (img_ptr)
		mlx_destroy_image(mlx_ptr, img_ptr);
}

void	ft_clean(t_val *val)
{
	img_destructor(val->mlx_ptr, val->game->no.img.img);
	img_destructor(val->mlx_ptr, val->game->so.img.img);
	img_destructor(val->mlx_ptr, val->game->ea.img.img);
	img_destructor(val->mlx_ptr, val->game->we.img.img);
	img_destructor(val->mlx_ptr, val->img_ptr);
	if (val->win_ptr)
		mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free_map(val->game);
	free(val->mlx_ptr);
	free(val);
}

t_val	*val_init(char *filename)
{
	t_val	*val;

	val = (t_val *)malloc(sizeof(t_val));
	if (!val)
		return (NULL);
	val->mlx_ptr = NULL;
	val->win_ptr = NULL;
	val->img_ptr = NULL;
	val->keys[0] = 0;
	val->keys[1] = 0;
	val->keys[2] = 0;
	val->keys[3] = 0;
	val->keys[4] = 0;
	val->keys[5] = 0;
	val->game = parsing(filename);
	if (!val->game)
		return (free(val), NULL);
	return (val);
}

t_val	*loading(char *filename)
{
	t_val	*val;

	val = val_init(filename);
	if (!val)
		return (NULL);
	val->mlx_ptr = mlx_init();
	if (!val->mlx_ptr)
		return (free(val), NULL);
	ft_open_textures(val);
	val->win_ptr = mlx_new_window(val->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!val->win_ptr)
		return (mlx_destroy_display(val->mlx_ptr), free(val), NULL);
	val->img_ptr = mlx_new_image(val->mlx_ptr, WIDTH, HEIGHT);
	if (!val->img_ptr)
		return (ft_clean(val), NULL);
	val->data.img_data = mlx_get_data_addr(val->img_ptr, &(val->data.bpp), \
		&(val->data.sline), &(val->data.endian));
	return (val);
}

int	main(int ac, char **av)
{
	t_val	*val;

	if (ac != 2)
		return (printf("usage:\n\t./cub3d <map filename>\n"), 1);
	val = loading(av[1]);
	if (!val)
		return (1);
	mlx_hooks(val);
	mlx_loop_hook(val->mlx_ptr, render, val);
	mlx_loop(val->mlx_ptr);
	ft_clean(val);
	return (0);
}
