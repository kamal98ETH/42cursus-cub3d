/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:12:38 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/05 16:13:24 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*------------------------------------------------------------------------------    TO BE DELETED      <-------*/
void affmap(t_game *map)
{
	printf("\n------------------------------ affichage -------------------------------\n");
	if(map)
	{
		if (map->ccol.stat)
			printf("ccol: %x\n", map->ccol.hexacode);
		if (map->ccol.stat)
			printf("fcol: %x\n", map->fcol.hexacode);
		if (map->no.path)
			printf("NO: %s\n", map->no.path);
		if (map->so.path)
			printf("SO: %s\n", map->so.path);
		if (map->ea.path)
			printf("EA: %s\n", map->ea.path);
		if (map->we.path)
			printf("WE: %s\n", map->we.path);
		if (map->dr.path)
			printf("DR: %s\n", map->dr.path);
		if (map->df.path)
			printf("DF: %s\n", map->df.path);
		printf("POS: %.2f , %.2f\n", map->plyr_x, map->plyr_y);
		printf("DIR: %.2f\n", map->plyr_dir);
		printf("--------------------------------- map ----------------------------------\n");
		if (map->map)
			{
				int i = 0;
				while(map->map[i])
				{
					printf("%s\n", map->map[i]);
					i++;
				}
			}
		else
			printf("No map found!\n");
	}
}
/*------------------------------------------------------------------------------    TO BE DELETED      <-------*/

void	map_init(t_game *map)
{
	map->ccol.stat = 0;
	map->fcol.stat = 0;
	map->plyr_x = 0;
	map->plyr_y = 0;
	map->map_x = 0;
	map->map_y = 0;
	map->no.path = NULL;
	map->ea.path = NULL;
	map->so.path = NULL;
	map->we.path = NULL;
	map->dr.path = NULL;
	map->df.path = NULL;
	map->en.path = NULL;
	map->map = NULL;
}

void	free_map(t_game *map)
{
	if (map)
	{
		if (map->no.path)
			free(map->no.path);
		if (map->so.path)
			free(map->so.path);
		if (map->ea.path)
			free(map->ea.path);
		if (map->we.path)
			free(map->we.path);
		if (map->dr.path)
			free(map->dr.path);
		if (map->df.path)
			free(map->df.path);
		if (map->en.path)
			free(map->en.path);
		if (map->map)
			free(map->map);
		free(map);
	}
}

void	get_player_direction(t_game *map, char flag)
{
	if (flag == 'E')
		map->plyr_dir = 0;
	else if (flag == 'W')
		map->plyr_dir = PI;
	else if (flag == 'N')
		map->plyr_dir = 0.5 * PI;
	else if (flag == 'S')
		map->plyr_dir = 1.5 * PI;
}

void	get_player_position(t_game *map)
{
	int		i;
	int		j;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S' \
			|| map->map[j][i] == 'W' || map->map[j][i] == 'E')
			{
				map->plyr_x = (double)(i * TILE + 20);
				map->plyr_y = (double)(j * TILE + 20);
				get_player_direction(map, map->map[j][i]);
				return ;
			}
			i++;
		}
		j++;
	}
}

int	get_enemy_position(t_game *map)
{
	int		i;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'X')
			{
				map->enemy_x = (double)(i * TILE + 20);
				map->enemy_y = (double)(j * TILE + 20);
				flag++;
			}
			i++;
		}
		j++;
	}
	return (flag);
}

t_game	*parsing(char *filename)
{
	char	*tmp;
	char	**arr;
	t_game	*map;

	if (!filename)
		return (NULL);
	tmp = get_data(filename);
	if (!tmp)
		return (NULL);
	arr = ft_split(tmp, '\n');
	map = data_treatment(arr, tmp);
	ft_free(arr);
	free(tmp);
	if (!map)
		return (NULL);
	affmap(map);
	return (map);
}
