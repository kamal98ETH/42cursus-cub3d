/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/09/29 17:47:16 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_val *val)
{
	float	x;
	float	y;

	if (keycode == 119) //forward
	{
		x = val->game->plyr_x + cos(val->game->plyr_dir) * MVTSPEED;
		y = val->game->plyr_y - sin(val->game->plyr_dir) * MVTSPEED;
	}
	else if (keycode == 115) //backward
	{
		x = val->game->plyr_x - cos(val->game->plyr_dir) * MVTSPEED;
		y = val->game->plyr_y + sin(val->game->plyr_dir) * MVTSPEED;
	}
	else if (keycode == 97) //left
	{
		x = val->game->plyr_x - cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y = val->game->plyr_y - sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	else // right
	{
		x = val->game->plyr_x + cos(PI /2 - val->game->plyr_dir) * MVTSPEED;
		y = val->game->plyr_y + sin(PI /2 - val->game->plyr_dir) * MVTSPEED;
	}
	if (inside_empty_space(*val, x, y))
	{
		val->game->plyr_x = x;
		val->game->plyr_y = y;
		// render(val);
	}
}

int key_hook(int keycode, t_val *val)
{
    // printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
        mlx_loop_end(val->mlx_ptr);
	if (keycode == 65361 || keycode == 65363)
	{
		if (keycode == 65361)
			val->game->plyr_dir = limit_angle(val->game->plyr_dir + RTTSPEED);
		else
			val->game->plyr_dir = limit_angle(val->game->plyr_dir - RTTSPEED);
		// render(val);
	}
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100)
		move_player(keycode, val);
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


void	color_map_pixel(t_val val, int x, int y, int color) //int x, int y
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

int	inside_empty_space(t_val val, float x, float y)
{
	int	X;
	int	Y;
	int	i;
	int	offset;

	X = floor(x);
	Y = floor(y);
	if (X >= val.game->map_x || Y >= val.game->map_y || X < 0 || Y < 0)
		return (0);
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
		return (1);
	if (offset <= val.game->map_size && val.game->map[offset] == '1')
		return (0);
	return (1);
}

void	draw_map(t_val *val)
{
	int	x = 0;
	int	y = 0;
	char c;

	while (y < val->game->map_y && y <= 720) //map height
	{
		while (x < val->game->map_x && x <= 1280) //map width
		{
			c = coordinates_to_tile(x, y, val->game->map).c;
			if (!(x % TILE) || !(y % TILE))
				color_map_pixel(*val, x/MSCALE, y/MSCALE, 0xc4c4c4);
			else if (c == '1')
				color_map_pixel(*val, x/MSCALE, y/MSCALE, 0xffffff);
			else
				color_map_pixel(*val, x/MSCALE, y/MSCALE, 0);
			x+=MSCALE;
		}
		x = 0;
		y += MSCALE;
	}
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
	// val->game->map_x = 1280;
	// val->game->map_y = 720;
	val->height = 720;
	val->width = 1280;

	if (!val->game->map)
	{
		free(val->game);
		free(val);
		return (1);
	}
	val->mlx_ptr = mlx_init();// check if these fail
	val->win_ptr = mlx_new_window(val->mlx_ptr, val->width, val->height, "cub3D");
	val->img_ptr = mlx_new_image(val->mlx_ptr, val->width, val->height);
	val->data.img_data = mlx_get_data_addr(val->img_ptr, &(val->data.bpp), &(val->data.sline), &(val->data.endian));
	val->img_map_ptr = mlx_new_image(val->mlx_ptr, 1280 /MSCALE, 720 /MSCALE);
	val->map_data.img_data = mlx_get_data_addr(val->img_map_ptr, &(val->map_data.bpp), &(val->map_data.sline), &(val->map_data.endian));
	mlx_hook(val->win_ptr, 2, (1L<<0), key_hook, val);
	// printf("player init coordinates: x: %f, y: %f\n", val->game->plyr_x, val->game->plyr_y);
	mlx_loop_hook(val->mlx_ptr, render, val);
	
	mlx_loop(val->mlx_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_map_ptr);
	mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free_game(val->game);
	free(val->mlx_ptr);
	free(val);
	return (0);
}
