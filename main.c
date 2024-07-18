/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/18 13:23:25 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_val *val)
{
	int	x;
	int	y;

	if (keycode == 119) //forward
	{
		x = val->game->plyr_x + round(cos(val->game->plyr_dir) * MVTSPEED);
		y = val->game->plyr_y - round(sin(val->game->plyr_dir) * MVTSPEED);
	}
	else if (keycode == 115) //backward
	{
		x = val->game->plyr_x - round(cos(val->game->plyr_dir) * MVTSPEED);
		y = val->game->plyr_y + round(sin(val->game->plyr_dir) * MVTSPEED);
	}
	else if (keycode == 97) //left
	{
		x = val->game->plyr_x - round(cos(PI /2 - val->game->plyr_dir) * MVTSPEED);
		y = val->game->plyr_y - round(sin(PI /2 - val->game->plyr_dir) * MVTSPEED);
	}
	else // right
	{
		x = val->game->plyr_x + round(cos(PI /2 - val->game->plyr_dir) * MVTSPEED);
		y = val->game->plyr_y + round(sin(PI /2 - val->game->plyr_dir) * MVTSPEED);
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

t_tile	coordinates_to_tile(int x, int y, char *map)
{
	t_tile	tile;
	int		i;

	tile.x = round(x / TILE);
	tile.y = round(y / TILE);
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
	char	c;

	c = coordinates_to_tile(round(x), round(y), val.game->map).c;
	if (c != '1' && c != '!'
		&& round(x) >= 0 && round(x) < val.game->map_x
		&& round(y) >= 0 && round(y) < val.game->map_y)
		return (1);
	return (0);
}

void	draw_map(t_val *val)
{
	int	x = 0;
	int	y = 0;
	char c;

	// while (y < val->game->map_y) //map height
	// {
	// 	while (x < val->game->map_x) //map width
	// 	{
	// 		c = coordinates_to_tile(x, y, val->game->map).c;
	// 		if (!(x % TILE) || !(y % TILE))
	// 			color_map_pixel(*val, x, y, 0xc4c4c4);
	// 		else if (c == '1')
	// 			color_map_pixel(*val, x, y, 0xffffff);
	// 		// else if (x == val.game->plyr_x && y == val.game->plyr_y)
	// 		// {
	// 		// 	// if (!val.game->plyr_x)
	// 		// 	// {
	// 		// 	// 	val.game->plyr_x = x + TILE /2;
	// 		// 	// 	val.game->plyr_y = y + TILE /2;
	// 		// 	// }
	// 		// 	color_map_pixel(val, xx yy;
	// 		// }
	// 		else
	// 			color_map_pixel(*val, x, y, 0);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }
	
	while (y < val->game->map_y) //map height
	{
		while (x < val->game->map_x) //map width
		{
			c = coordinates_to_tile(x, y, val->game->map).c;
			if (!(x % TILE) || !(y % TILE))
				color_map_pixel(*val, x/2, y/2, 0xc4c4c4);
			else if (c == '1')
				color_map_pixel(*val, x/2, y/2, 0xffffff);
			// else if (x == val.game->plyr_x && y == val.game->plyr_y)
			// {
			// 	// if (!val.game->plyr_x)
			// 	// {
			// 	// 	val.game->plyr_x = x + TILE /2;
			// 	// 	val.game->plyr_y = y + TILE /2;
			// 	// }
			// 	color_map_pixel(val, xx yy;
			// }
			else
				color_map_pixel(*val, x/2, y/2, 0);
			x+=2;
		}
		x = 0;
		y+=2;
	}
}

void	ray_casting()
{
	
}

void	test(t_val *val)
{
	

	// printf("%s", map);
	// printf("\n\ntile x: %d, tile y: %d, tile c: %c\n", tile1.x, tile1.y, tile1.c);
	// printf("coordinates x: %d, coordinates y: %d\n", coordinates2.x, coordinates2.y);

	draw_map(val);
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

	val->game->plyr_x = 434; // should not be hard coded
	val->game->plyr_y = 78; // should not be hard coded
	val->game->plyr_dir = 0.017183 * PI; // should not be hard coded
	
	val->game->map = hard_coded_map();
	if (!val->game->map)
	{
		free(val->game);
		free(val);
		return (1);
	}
	val->rays = (float *)malloc(RAYS * sizeof(float)); // maybe won't need this
	if (!val->rays)
	{
		free(val->game->map);
		free(val->game);
		free(val);
		return (1);
	}
	val->mlx_ptr = mlx_init();// check if these fail
	val->win_ptr = mlx_new_window(val->mlx_ptr, val->width, val->height, "cub3D");
	val->img_ptr = mlx_new_image(val->mlx_ptr, val->width, val->height);
	// val->img_map_ptr = mlx_new_image(val->mlx_ptr, val->game->map_x, val->game->map_y);
	val->img_map_ptr = mlx_new_image(val->mlx_ptr, val->game->map_x /2, val->game->map_y /2);
	mlx_key_hook(val->win_ptr, key_hook, val);

	printf("player init coordinates: x: %d, y: %d\n", val->game->plyr_x, val->game->plyr_y);
	// draw_map(*val);
	// test(*val);
	render(val);
	
	mlx_loop(val->mlx_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_ptr);
	mlx_destroy_image(val->mlx_ptr, val->img_map_ptr);
	mlx_destroy_window(val->mlx_ptr, val->win_ptr);
	mlx_destroy_display(val->mlx_ptr);
	free(val->rays);
	free(val->game->map);
	free(val->game);
	free(val->mlx_ptr);
	free(val);
	return (0);
}


// t_tile	coordinates_to_tile(t_coordinates coordinates, char *map)
// {
// 	t_tile	tile;
// 	int		i;

// 	tile.x = coordinates.x / TILE;
// 	tile.y = coordinates.y / TILE;
// 	// you should handle maps that isn't squares
// 	i = 0;
// 	while (tile.y != i)
// 	{
// 		while (*map != '\n')
// 			map++;
// 		map++;
// 		i++;
// 	}
// 	tile.c = map[tile.x];
// 	return (tile);
// }

// void	draw_rays(t_val val, char *map, float p_dir)
// {
// 	int	i = 0;
// 	int	height = 0;
// 	int	opposite;
// 	int	adjacent;
// 	float	angle;
// 	int	x;
// 	char	c;

// 	angle = p_dir - FOV / 2;
// 	while (i < RAYS)
// 	{
// 		height = val.game->plyr_y;
// 		while (height >= 0)
// 		{
// 			if (angle < PI / 2)
// 			{
// 				opposite = val.game->plyr_y - height;
// 				adjacent = opposite / tan(angle);
// 				x = adjacent + val.game->plyr_x;
// 				c = coordinates_to_tile(x, height, map).c;
// 				if (c == '1' || c == '!')
// 					break;
// 				color_pixel(val, x, height, 0x7e00ff);
// 			}
// 			else if (angle < PI)
// 			{
// 				opposite = val.game->plyr_y - height;
// 				adjacent = opposite / tan(PI - angle);
// 				x = val.game->plyr_x - adjacent;
// 				c = coordinates_to_tile(x, height, map).c;
// 				if (c == '1' || c == '!')
// 					break;
// 				color_pixel(val, x, height, 0x7e00ff);
// 			}
// 			else if (angle < (3 * PI) / 2)
// 			{
// 				opposite = val.game->plyr_y - height;
// 				adjacent = opposite / tan(angle - PI);
// 				x = val.game->plyr_x - adjacent;
// 				c = coordinates_to_tile(x, val.game->plyr_y + height % val.game->plyr_y, map).c;
// 				if (c == '1' || c == '!')
// 					break;
// 				color_pixel(val, x, val.game->plyr_y + height % val.game->plyr_y, 0x7e00ff);
// 			}
// 			else
// 			{
				
// 			}
// 			height--;
// 		}
// 		angle += FOV / RAYS;
// 		i++;
// 	}
	



	
// }
// void	draw_north_east_rays(t_val val, char *map, float angle)
// {
// 	int	a;
// 	int	x;
// 	int y;

// 	a = tan(angle);
// 	y = 0;
// 	while (y < val.game->map_y)
// 	{
// 		x = 0;
// 		while (x < val.game->map_x)
// 		{
// 			if (round(y) == round(a * x))
// 			{
// 				color_pixel(val, x, y, 0xffffff);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	// int	opposite;
// 	// int	adjacent;
// 	// int	height;
// 	// int	x;
// 	// int	y;
// 	// char c;
	
// 	// height = val.game->plyr_y;
// 	// while (height >= 0)
// 	// {
// 	// 	opposite = val.game->plyr_y - height;
// 	// 	adjacent = opposite / tan(angle);
// 	// 	x = val.game->plyr_x + adjacent;
// 	// 	y = height;
// 	// 	c = coordinates_to_tile(x, y, map).c;
// 	// 	if (c == '1' || c == '!')
// 	// 		break;
// 	// 	color_pixel(val, round(x), round(y), 0x7e00ff);
// 	// 	height--;
// 	// }
	
// }

// void	draw_north_west_rays(t_val val, char *map, float angle)
// {
// 	int	opposite;
// 	int	adjacent;
// 	int	height;
// 	int	x;
// 	int	y;
// 	char c;
	
// 	height = val.game->plyr_y;
// 	while (height >= 0)
// 	{
// 		opposite = val.game->plyr_y - height;
// 		adjacent = opposite / tan(PI - angle);
// 		x = val.game->plyr_x - adjacent;
// 		y = height;
// 		c = coordinates_to_tile(x, y, map).c;
// 		if (c == '1' || c == '!')
// 			break;
// 		color_pixel(val, round(x), round(y), 0x7e00ff);
// 		height--;
// 	}
	
// }

// void	draw_south_west_rays(t_val val, char *map, float angle)
// {
// 	int	opposite;
// 	int	adjacent;
// 	int	height;
// 	int	x;
// 	int	y;
// 	char c;
	
// 	height = val.game->plyr_y;
// 	while (height < val.game->map_y)
// 	{
// 		opposite = height - val.game->plyr_y;
// 		adjacent = opposite / tan(angle - PI);
// 		x = val.game->plyr_x - adjacent;
// 		y = height;
// 		c = coordinates_to_tile(x, y, map).c;
// 		if (c == '1' || c == '!')
// 			break;
// 		color_pixel(val, round(x), round(y), 0x7e00ff);
// 		height++;
// 	}
	
// }

// void	draw_south_east_rays(t_val val, char *map, float angle)
// {
// 	int	opposite;
// 	int	adjacent;
// 	int	height;
// 	int	x;
// 	int	y;
// 	char c;
	
// 	height = val.game->plyr_y;
// 	while (height < val.game->map_y)
// 	{
// 		opposite = height - val.game->plyr_y;
// 		adjacent = opposite / tan(angle - 3 * PI / 2);
// 		x = val.game->plyr_x + adjacent;
// 		y = height;
// 		c = coordinates_to_tile(x, y, map).c;
// 		if (c == '1' || c == '!')
// 			break;
// 		color_pixel(val, round(x), round(y), 0x7e00ff);
// 		height++;
// 	}
	
// }