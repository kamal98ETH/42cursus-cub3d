/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/08 19:52:06 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int keycode, t_val *val)
{
	if (keycode == 119) //forward
		{
			val->game->plyr_x += round(cos(val->game->plyr_dir) * 5);
			val->game->plyr_y -= round(sin(val->game->plyr_dir) * 5);
		}
		else if (keycode == 115) //backward
		{
			val->game->plyr_x -= round(cos(val->game->plyr_dir) * 5);
			val->game->plyr_y += round(sin(val->game->plyr_dir) * 5);
		}
		else if (keycode == 97) //left
		{
			val->game->plyr_x -= round(cos(PI /2 - val->game->plyr_dir) * 5);
			val->game->plyr_y -= round(sin(PI /2 - val->game->plyr_dir) * 5);
		}
		else // right
		{
			val->game->plyr_x += round(cos(PI /2 - val->game->plyr_dir) * 5);
			val->game->plyr_y += round(sin(PI /2 - val->game->plyr_dir) * 5);
		}
		render(val);
}

int key_hook(int keycode, t_val *val)
{
    // printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
        mlx_loop_end(val->mlx_ptr);
	if (keycode == 65361 || keycode == 65363)
	{
		if (keycode == 65361)
			val->game->plyr_dir = limit_angle(val->game->plyr_dir + PI / 10);
		else
			val->game->plyr_dir = limit_angle(val->game->plyr_dir - PI / 10);
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

void	color_pixel(t_val val, int map, int *coordinates, int color) //int x, int y
{
	char	*img_data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		offset;

	if (coordinates[0] < 0 || coordinates[1] < 0 || coordinates[0] >= val.width || coordinates[1] >= val.height)
		return ;
	// try to save img data and bit per pixel and size line in mlx struct to color the wanted pixel without having to call mlx_gat_data_addr each time you color a pixel
	if (map)
		img_data = mlx_get_data_addr(val.img_map_ptr, &bits_per_pixel, &size_line, &endian);
	else
		img_data = mlx_get_data_addr(val.img_ptr, &bits_per_pixel, &size_line, &endian);
	offset = coordinates[1] * size_line + coordinates[0] * (bits_per_pixel / 8);
	*(int *)(img_data + offset) = color;
}

t_coordinates	tile_to_coordinates(t_tile tile)
{
	t_coordinates	coordinates;

	coordinates.x = tile.x * TILE_SIZE + TILE_SIZE /2;
	coordinates.y = tile.y * TILE_SIZE + TILE_SIZE /2;
	return (coordinates);
}

t_tile	coordinates_to_tile(int x, int y, char *map)
{
	t_tile	tile;
	int		i;

	tile.x = x / TILE_SIZE;
	tile.y = y / TILE_SIZE;
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

int	draw_line(t_val val, double angle)
{
	int length = 1;
	char c;
	int x0 = val.game->plyr_x;
	int y0 = val.game->plyr_y;
	int x1;
	int y1;

	// calculate line len
	while (1)
	{
		x1 = x0 + round(length * cos(angle));
		y1 = y0 - round(length * sin(angle)); // - instead of + like the previous is becouse y axis is the opposite direction of a normal plan
		c = coordinates_to_tile(x1, y1, val.game->map).c;
		if (c == '1')
			break;
		length++;
	}
	// if (angle > PI) // to be investigated
	length--;
	x1 = x0 + round(length * cos(angle));
	y1 = y0 + round(length * sin(angle));

    int dx = x1 - x0;
    int dy = y0 - y1; // same here as y0 - len...
    
	int steps = abs(dy);
	if (abs(dx) > abs(dy))
		steps = abs(dx);

    float x_inc = dx / (float) steps;
    float y_inc = dy / (float) steps;

	int	coordinates[2];
    float x = x0;
    float y = y0;
	coordinates[0] = round(x); 
	coordinates[1] = round(y); 
    for (int i = 0; i <= steps; i++) {
        color_pixel(val, 1, coordinates, 0xff11ff);
        x += x_inc;
        y += y_inc;
		coordinates[0] = round(x); 
		coordinates[1] = round(y); 
    }
	return (length);
}

void	draw_rays(t_val *val)
{
	float	angle;
	int		i;
	// int		*rays;

	angle = limit_angle(val->game->plyr_dir + FOV /2);
	i = 0;
	while (i < RAYS)
	{
		val->rays[i] = draw_line(*val, angle);
		angle = limit_angle(angle - FOV / RAYS);
		i++;
	}
	// return (rays);
}

void	draw_map(t_val *val)
{
	int	coordinates[2];
	coordinates[0] = 0;
	coordinates[1] = 0;
	char c;

	while (coordinates[1] < 130) //map height
	{
		while (coordinates[0] < 200) //map width
		{
			c = coordinates_to_tile(coordinates[0], coordinates[1], val->game->map).c;
			if (c == '1')
				color_pixel(*val, 1, coordinates, 0xffffff);
			// else if (x == val.game->plyr_x && y == val.game->plyr_y)
			// {
			// 	// if (!val.game->plyr_x)
			// 	// {
			// 	// 	val.game->plyr_x = x + TILE_SIZE /2;
			// 	// 	val.game->plyr_y = y + TILE_SIZE /2;
			// 	// }
			// 	color_pixel(val, x, y, 0xff00ff);
			// }
			else
				color_pixel(*val, 1, coordinates, 0);
			coordinates[0]++;
		}
		coordinates[0] = 0;
		coordinates[1]++;
	}
	// color_pixel(val, 250, 250, 0xffffff);
	draw_rays(val);
	// mlx_put_image_to_window(val.mlx_ptr, val.win_ptr, val.img_map_ptr, 0, 0);
	// printf("player dir is: %f PI\n", val.game->plyr_dir / PI);
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
	map = (char *)malloc(273);
	if (!map)
		return NULL;
	int		map_fd = open("test.cub", O_RDONLY);
	read(map_fd, map, 273);
	close(map_fd);
	map[272] = 0;
	return (map);
}

void	draw_walls(t_val *val)
{
	// int	*rays;
	float	wall_height;
	int y_top;
	int y;
	int	x;
	int	coordinates[2];
	float	ray_angle;

	// draw_rays(val);
	x = 0;
	ray_angle = limit_angle(val->game->plyr_dir + FOV /2);
	while (x < RAYS)
	{
		val->rays[x] *= cos(limit_angle(- ray_angle + val->game->plyr_dir));
		// wall_height = val->height / val->rays[x];
		wall_height = (20 / val->rays[x]) * ((val->width / 2) / tan(FOV / 2));
		printf("wall height is: %f\n", wall_height);
		y_top = round((val->height / 2) - (wall_height / 2));
		y = 0;
		while (y < val->height)
		{
			coordinates[0] = x;
			coordinates[1] = y;
			if (y < y_top + round(wall_height) && y > y_top)
				color_pixel(*val, 0, coordinates, 0xe5d9d2);
			else if (y < y_top)
				color_pixel(*val, 0, coordinates, 0x87ceeb);
			else
				color_pixel(*val, 0, coordinates, 0x543b0e);
			y++;
		}
		ray_angle = limit_angle(ray_angle - FOV / RAYS);
		x++;
	}
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_ptr, 0, 0);
}

void	render(t_val *val)
{
	draw_map(val);
	for (int i = 0; i < RAYS; i++)
		printf("%f, ", val->rays[i]);
	printf("\n\n\n");
	draw_walls(val);
	mlx_put_image_to_window(val->mlx_ptr, val->win_ptr, val->img_map_ptr, 0, 0);
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
	val->game->plyr_x = 35; // should not be hard coded
	val->game->plyr_y = 85; // should not be hard coded
	val->game->map_x = 200; // should not be hard coded
	val->game->map_y = 130; // should not be hard coded
	val->game->plyr_dir = PI / 2; // should not be hard coded
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
	val->img_map_ptr = mlx_new_image(val->mlx_ptr, 200, 200);
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

// 	tile.x = coordinates.x / TILE_SIZE;
// 	tile.y = coordinates.y / TILE_SIZE;
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