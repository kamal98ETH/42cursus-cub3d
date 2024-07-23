/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/23 18:41:38 by kez-zoub         ###   ########.fr       */
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
		render(val);
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
		render(val);
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
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	// try to save img data and bit per pixel and size line in mlx struct to color the wanted pixel without having to call mlx_gat_data_addr each time you color a pixel
	img_data = mlx_get_data_addr(val.img_map_ptr, &bits_per_pixel, &size_line, &endian);
	
	offset = y * size_line + x * (bits_per_pixel / 8);
	*(int *)(img_data + offset) = color;
}

void	color_game_pixel(t_val val, int x, int y, int color)
{
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		offset;

	if (x < 0 || y < 0 || x >= val.width || y >= val.height)
		return ;
	// try to save img data and bit per pixel and size line in mlx struct to color the wanted pixel without having to call mlx_gat_data_addr each time you color a pixel
	img_data = mlx_get_data_addr(val.img_ptr, &bits_per_pixel, &size_line, &endian);
	offset = y * size_line + x * (bits_per_pixel / 8);
	*(int *)(img_data + offset) = color;
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
		while (val.game->map[offset] != '\n')
			offset++;
		offset++;
		i++;
	}
	offset += X;
	if (val.game->map[offset] == '1')
		return (0);
	return (1);

	// char	c;

	// c = coordinates_to_tile(x, y, val.game->map).c;
	// if (c != '1' && c != '!')
	// 	// && round(x) >= 0 && round(x) < val.game->map_x
	// 	// && round(y) >= 0 && round(y) < val.game->map_y)
	// 	return (1);
	// return (0);
}

void	draw_map(t_val *val)
{
	int	x = 0;
	int	y = 0;
	char c;
	
	while (y < val->game->map_y) //map height
	{
		while (x < val->game->map_x) //map width
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

char	*hard_coded_map()
{
	char	*map;
	map = (char *)malloc(420);
	if (!map)
		return NULL;
	int		map_fd = open("test.cub", O_RDONLY);
	read(map_fd, map, 420);
	close(map_fd);
	map[419] = 0;
	return (map);
}

int	main()
{
	t_val	*val;
	
	val = (t_val *)malloc(sizeof(t_val));
	if (!val)
		return (1);
	val->game = (t_game *)malloc(sizeof(t_game));
	if (!val->game)
	{
		free(val);
		return (1);
	}
	val->height = 720;
	val->width = 1280;
	val->game->map_x = 800; // should not be hard coded
	val->game->map_y = 800; // should not be hard coded

	val->game->plyr_x = 256; // should not be hard coded
	val->game->plyr_y = 200; // should not be hard coded
	val->game->plyr_dir = 0.5 * PI; // should not be hard coded
	
	val->game->map = hard_coded_map();
	if (!val->game->map)
	{
		free(val->game);
		free(val);
		return (1);
	}
	val->mlx_ptr = mlx_init();// check if these fail
	val->win_ptr = mlx_new_window(val->mlx_ptr, val->width, val->height, "cub3D");
	val->img_ptr = mlx_new_image(val->mlx_ptr, val->width, val->height);
	// val->img_map_ptr = mlx_new_image(val->mlx_ptr, val->game->map_x, val->game->map_y);
	val->img_map_ptr = mlx_new_image(val->mlx_ptr, val->game->map_x /MSCALE, val->game->map_y /MSCALE);
	mlx_key_hook(val->win_ptr, key_hook, val);

	printf("player init coordinates: x: %f, y: %f\n", val->game->plyr_x, val->game->plyr_y);
	render(val);
	
	mlx_loop(val->mlx_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_map_ptr);
	mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free(val->game->map);
	free(val->game);
	free(val->mlx_ptr);
	free(val);
	return (0);
}
