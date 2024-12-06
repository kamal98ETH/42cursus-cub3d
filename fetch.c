/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:12:07 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/06 10:25:45 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fetch_color(t_game *map, char **elems, int opt)
{
	int	i;
	int	flag;
	int	tab[3];

	i = 0;
	flag = 0;
	if (!opt && map->ccol.stat == 0)
	{
		map->ccol.stat = 1;
		while (elems[++i] && i < 4)
			tab[i - 1] = unique_atoi(elems[i], &flag);
		map->ccol.hexacode = tab[2] + tab[1] * 256 + tab[0] * 256 * 256;
	}
	else if (opt && map->fcol.stat == 0)
	{
		map->fcol.stat = 1;
		while (elems[++i] && i < 4)
			tab[i - 1] = unique_atoi(elems[i], &flag);
		map->fcol.hexacode = tab[2] + tab[1] * 256 + tab[0] * 256 * 256;
	}
	else
		return (0);
	if (i != 4 || flag)
		return (0);
	return (1);
}

int	fetch_texture(t_game *map, char **elems, int flag)
{
	if (elems[1] && elems[2])
		return (0);
	if (flag == 1 && elems[1] && !map->no.path)
		map->no.path = ft_strdup(elems[1]);
	else if (flag == 2 && elems[1] && !map->so.path)
		map->so.path = ft_strdup(elems[1]);
	else if (flag == 3 && elems[1] && !map->ea.path)
		map->ea.path = ft_strdup(elems[1]);
	else if (flag == 4 && elems[1] && !map->we.path)
		map->we.path = ft_strdup(elems[1]);
	else if (flag == 5 && elems[1] && !map->dr.path)
		map->dr.path = ft_strdup(elems[1]);
	else if (flag == 6 && elems[1] && !map->df.path)
		map->df.path = ft_strdup(elems[1]);
	else if (flag == 7 && elems[1] && !map->en.path)
		map->en.path = ft_strdup(elems[1]);
	else
		return (0);
	return (1);
}

int	get_elements(t_game *map, char *str)
{
	char	**elems;
	int		flag;

	flag = 0;
	if (coma_check(str))
		return (0);
	elems = multi_split(str, "\t\n\v\f\r ,");
	if (elems[0] && !ft_strncmp(elems[0], "C", 2))
		flag = fetch_color(map, elems, 0);
	else if (elems[0] && !ft_strncmp(elems[0], "F", 2))
		flag = fetch_color(map, elems, 1);
	else if (elems[0] && !ft_strncmp(elems[0], "NO", 3))
		flag = fetch_texture(map, elems, 1);
	else if (elems[0] && !ft_strncmp(elems[0], "SO", 3))
		flag = fetch_texture(map, elems, 2);
	else if (elems[0] && !ft_strncmp(elems[0], "EA", 3))
		flag = fetch_texture(map, elems, 3);
	else if (elems[0] && !ft_strncmp(elems[0], "WE", 3))
		flag = fetch_texture(map, elems, 4);
	else if (elems[0] && !ft_strncmp(elems[0], "DR", 3))
		flag = fetch_texture(map, elems, 5);
	else if (elems[0] && !ft_strncmp(elems[0], "DF", 3))
		flag = fetch_texture(map, elems, 6);
	else if (elems[0] && !ft_strncmp(elems[0], "X", 2))
		flag = fetch_texture(map, elems, 7);
	else
		return (ft_free(elems), 0);
	return (ft_free(elems), flag);
}

int	check_filename_extension(t_game m)
{
	const char	*t;

	t = ".xpm";
	if (m.ea.path && ft_strncmp(m.ea.path + ft_strlen(m.ea.path) - 4, t, 5))
		return (1);
	if (m.we.path && ft_strncmp(m.we.path + ft_strlen(m.we.path) - 4, t, 5))
		return (1);
	if (m.no.path && ft_strncmp(m.no.path + ft_strlen(m.no.path) - 4, t, 5))
		return (1);
	if (m.so.path && ft_strncmp(m.so.path + ft_strlen(m.so.path) - 4, t, 5))
		return (1);
	if (m.dr.path && ft_strncmp(m.dr.path + ft_strlen(m.dr.path) - 4, t, 5))
		return (1);
	if (m.df.path && ft_strncmp(m.df.path + ft_strlen(m.df.path) - 4, t, 5))
		return (1);
	if (m.en.path && ft_strncmp(m.en.path + ft_strlen(m.en.path) - 4, t, 5))
		return (1);
	return (0);
}

t_game	*data_treatment(char **arr, char *content)
{
	int		i;
	int		n;
	t_game	*map;

	i = 0;
	map = malloc(sizeof(t_game));
	if (!map)
		return (NULL);
	map_init(map);
	while (arr[i] && i < 9)
	{
		if (!get_elements(map, arr[i]))
		{
			printf("\e[31m>> [PARSING ERORR] bad element!\e[0m \n");
			return (free_map(map), NULL);
		}
		i++;
	}
	if (check_filename_extension(*map))
		handle_map_error(-5);
	else if (arr[i] && check_if_map(arr[i]))
		return (get_map(arr + i, content, map));
	else if (!arr[i])
		handle_map_error(-3);
	else
		handle_map_error(-4);
	return (free_map(map), NULL);
}
