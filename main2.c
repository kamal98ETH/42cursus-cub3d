/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:12:38 by laoubaid          #+#    #+#             */
/*   Updated: 2024/10/31 18:15:58 by laoubaid         ###   ########.fr       */
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
		printf("POS: %.2f , %.2f\n", map->plyr_x, map->plyr_y);
		printf("DIR: %.2f\n", map->plyr_dir);
		printf("--------------------------------- map ----------------------------------\n");
		if (map->map)
			printf("%s\n", map->map);
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

void	get_player_position(t_game *map, char **tmp)
{
	int		i;
	int		j;

	j = 0;
	while (tmp[j])
	{
		i = 0;
		while (tmp[j][i])
		{
			if (tmp[j][i] == 'N' || tmp[j][i] == 'S' \
			|| tmp[j][i] == 'W' || tmp[j][i] == 'E')
			{
				map->plyr_x = (float)(i * TILE + 20);
				map->plyr_y = (float)(j * TILE + 20);
				get_player_direction(map, tmp[j][i]);
				return ;
			}
			i++;
		}
		j++;
	}
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
	map->map_size = ft_strlen(map->map);
	return (map);
}
