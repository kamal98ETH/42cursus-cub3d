/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/11/10 16:51:27 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_val *val)
{
	float	x;
	float	y;
	int		flag;

	flag = 0;
	if (val->keys[LA_K])
		val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
	if (val->keys[RA_K])
		val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
	x = val->game->plyr_x;
	y = val->game->plyr_y;
	if (val->keys[W_K]) // forward
	{
		// printf("forward\n");
		flag++;
		x += cos(val->game->plyr_dir) * MVTSPEED;
		y -= sin(val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[S_K]) // backward
	{
		// printf("backward\n");
		flag++;
		x -= cos(val->game->plyr_dir) * MVTSPEED;
		y += sin(val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[A_K]) // left
	{
		// printf("left\n");
		flag++;
		x -= cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y -= sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (val->keys[D_K]) // right
	{
		// printf("right\n");
		flag++;
		x += cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y += sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (flag && corresponding_tile(*val, x, y) == 0)
	{
		val->game->plyr_x = x;
		val->game->plyr_y = y;
	}
}

int key_hook_press(int keycode, t_val *val)
{
    // printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
        mlx_loop_end(val->mlx_ptr);
	if (keycode == W_KEYCODE)
		val->keys[W_K] = 1;
	if (keycode == S_KEYCODE)
		val->keys[S_K] = 1;
	if (keycode == A_KEYCODE)
		val->keys[A_K] = 1;
	if (keycode == D_KEYCODE)
		val->keys[D_K] = 1;
	if (keycode == LA_KEYCODE)
		val->keys[LA_K] = 1;
	if (keycode == RA_KEYCODE)
		val->keys[RA_K] = 1;
    return (0);
}

int key_hook_release(int keycode, t_val *val)
{
	if (keycode == W_KEYCODE)
		val->keys[W_K] = 0;
	if (keycode == S_KEYCODE)
		val->keys[S_K] = 0;
	if (keycode == A_KEYCODE)
		val->keys[A_K] = 0;
	if (keycode == D_KEYCODE)
		val->keys[D_K] = 0;
	if (keycode == LA_KEYCODE)
		val->keys[LA_K] = 0;
	if (keycode == RA_KEYCODE)
		val->keys[RA_K] = 0;
    return (0);
}

float	limit_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}


void	color_map_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	offset = y * val.map_data.sline + x * (val.map_data.bpp / 8);
	*(int *)(val.map_data.img_data + offset) = color;
}

void	color_game_pixel(t_val val, int x, int y, int color)
{
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	offset = y * val.data.sline + x * (val.data.bpp / 8);
	*(int *)(val.data.img_data + offset) = color;
}

t_coordinates	tile_to_coordinates(t_tile tile)
{
	t_coordinates	coordinates;

	coordinates.x = tile.x * TILE + TILE /2;
	coordinates.y = tile.y * TILE + TILE /2;
	return (coordinates);
}

t_tile	coordinates_to_tile(float x, float y, char *map)
{
	t_tile	tile;
	int		i;

	tile.x = floor(x / TILE);
	tile.y = floor(y / TILE);
	// you should handle maps that isn't squares
	i = 0;
	while (*map && tile.y != i) // to be reviewed
	{
		while (*map && *map != '\n')
			map++;
		if (*map)
			map++;
		i++;
	}
	if (tile.x > ft_strlen(map) || !*map) // to be reviewed (in case the coordinates are out of the map)
		tile.c = '!';
	else
		tile.c = map[tile.x];
	return (tile);
}

int	corresponding_tile(t_val val, float x, float y)
{
	int	X;
	int	Y;
	int	i;
	int	offset;

	X = floor(x);
	Y = floor(y);
	if (X < 0 || Y < 0)
		return (-1);
	X /= TILE;
	Y /= TILE;
	i = 0;
	offset = 0;
	while (i < Y)
	{
		while (val.game->map[offset] && val.game->map[offset] != '\n')
			offset++;
		if (val.game->map[offset])
			offset++;
		i++;
	}
	if (val.game->map[offset])
		offset += X;
	else
		return (-1);
	if (offset <= val.game->map_size && val.game->map[offset] == '1')// map size ???? what if offset > map_size
		return (1);
	if (offset <= val.game->map_size && val.game->map[offset] == '2')// map size ???? what if offset > map_size
		return (2);
	return (0);
}

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
	val->height = 720;
	val->width = 1280;

	//to be deleted
	// printf("map x: %d, map y: %d\n", val->game->map_x, val->game->map_y);
	// val->game->plyr_x = 163.534042;
	// val->game->plyr_y = 411.003113;
	// val->game->plyr_dir = 1.435832 * PI;

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
	

	mlx_hook(val->win_ptr, KeyPress, KeyPressMask, key_hook_press, val);
	mlx_hook(val->win_ptr, KeyRelease, KeyReleaseMask, key_hook_release, val);
	// printf("player init coordinates: x: %f, y: %f\n", val->game->plyr_x, val->game->plyr_y);
	mlx_loop_hook(val->mlx_ptr, render, val);
	// render(val);
	mlx_loop(val->mlx_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_map_ptr);
	mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free_map(val->game);
	free(val->mlx_ptr);
	free(val);
	return (0);
}
