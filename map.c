/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:13 by laoubaid          #+#    #+#             */
/*   Updated: 2024/10/11 10:05:17 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_init(t_game *map)
{
	map->ccol.stat = 0;
	map->fcol.stat = 0;
	map->plyr_x = 0;
	map->plyr_y = 0;
	map->no.path = NULL;
	map->ea.path = NULL;
	map->so.path = NULL;
	map->we.path = NULL;
	map->map = NULL;
}

char	*get_data(char *str)
{
	char	*tmp;
	int		fd;
	int		rsize;
	char	buff[1025];

	tmp = NULL;
	rsize = 0;
	ft_bzero(buff, 1025);
	if (!check_name(str))
		return (NULL);
	fd = open(str, O_RDWR);
	if (fd == -1)
		return (NULL);
	rsize = read(fd, buff, 1024);
	while (rsize)
	{
		tmp = join_optclean(tmp, buff, 1);
		rsize = read(fd, buff, 1024);
		if (rsize >= 0)
			buff[rsize] = 0;
	}
	return (tmp);
}

void	handle_map_error(int flag)
{
	if (flag == -4)
		printf("\e[31m>> [PARSING ERORR] bad element!\e[0m \n");
	else if (flag == -3)
		printf("\e[31m>> [PARSING ERORR] missing elements!\e[0m \n");
	else if (flag == -2)
		printf("\e[31m>> [PARSING ERORR] empty line in map!\e[0m \n");
	else if (flag == -1)
		write(2, "\e[31mError\e[0m\nMap not closed!\n", 32);
	else if (flag == 0)
		write(2, "\e[31mError\e[0m\nUnknown start position!\n", 40);
	else if (flag > 1)
		write(2, "\e[31mError\e[0m\nMultiple start positions!\n", 42);
}

char	**square_format(char **str)
{
	int		i;
	int		j;
	int		k;
	int		max;
	char	**tmp;

	i = 0;
	max = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > max)
			max = ft_strlen(str[i]);
		i++;
	}
	tmp = malloc(sizeof(char *) * (i + 1));
	tmp[i] = NULL;
	i = 0;
	while (str[i])
	{
		tmp[i] = malloc(max + 1);
		j = 0;
		k = 0;
		while (j <= max)
		{
			tmp[i][j] = 0;
			if (str[i][k])
				tmp[i][j] = str[i][k++];
			j++;
		}
		i++;
	}
	return (tmp);
}

t_game	*get_map(char **str, char *content, t_game *map)
{
	int		i;
	int		flag;
	char	*new;
	char	*tmp;

	i = 0;
	tmp = ft_strnstr(content, str[0], ft_strlen(content));
	if (ft_strnstr(tmp, "\n\n", ft_strlen(tmp)))
		return (free(map), handle_map_error(-2), NULL);
	flag = check_map_validation(square_format(str), &i);
	if (flag != 1)
		return (free(map), handle_map_error(flag), NULL);
	new = NULL;
	i = 0;
	flag = 0;
	while (str[i])
	{
		flag = ft_strlen(str[i]);
		if (flag > map->map_x)
			map->map_x = flag;
		new = join_optclean(new, str[i], 1);
		new = join_optclean(new, "\n", 1);
		i++;
	}
	map->map_y = i * TILE;
	map->map_x = map->map_x * TILE;
	map->map = new;
	get_player_position(map, str);
	return (map);
}
