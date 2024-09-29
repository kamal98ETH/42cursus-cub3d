/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:12:38 by laoubaid          #+#    #+#             */
/*   Updated: 2024/09/29 15:15:22 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *map)
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
			if (tmp[j][i] == 'N' || tmp[j][i]  == 'S' || tmp[j][i]  == 'W' || tmp[j][i]  == 'E')
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
	map->map_size = ft_strlen(map->map);
	ft_free(arr);
	free(tmp);
	return (map);
}
