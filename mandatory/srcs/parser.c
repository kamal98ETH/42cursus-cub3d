/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:12:38 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 18:53:36 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_init(t_game **map)
{
	t_game	*tmp;

	tmp = (t_game *)malloc(sizeof(t_game));
	if (!tmp)
		return (1);
	tmp->ccol.stat = 0;
	tmp->fcol.stat = 0;
	tmp->plyr_x = 0;
	tmp->plyr_y = 0;
	tmp->map_x = 0;
	tmp->map_y = 0;
	tmp->no.path = NULL;
	tmp->ea.path = NULL;
	tmp->so.path = NULL;
	tmp->we.path = NULL;
	tmp->map = NULL;
	*map = tmp;
	return (0);
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
	int	i;
	int	j;

	j = 0;
	while (map->map[j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (map->map[j][i] == 'N' || map->map[j][i] == 'S' \
			|| map->map[j][i] == 'W' || map->map[j][i] == 'E')
			{
				map->plyr_x = (double)(i * TILE + TILE / 2);
				map->plyr_y = (double)(j * TILE + TILE / 2);
				get_player_direction(map, map->map[j][i]);
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
	return (map);
}
