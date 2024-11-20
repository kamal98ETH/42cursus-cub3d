/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:13 by laoubaid          #+#    #+#             */
/*   Updated: 2024/11/09 04:46:36 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (flag == -5)
		printf("\e[31m>> [TEXTURE ERORR] only .xpm file!\e[0m \n");
	else if (flag == -4)
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

char	**allocate_square_space(char **str, t_game *map)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (ft_strlen(str[i]) > map->map_x)
			map->map_x = ft_strlen(str[i]);
		i++;
	}
	map->map_y = i * TILE;
	tmp = malloc(sizeof(char *) * (i + 1));
	tmp[i] = NULL;
	return (tmp);
}

char	**square_format(char **str, t_game *map)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	i = 0;
	tmp = allocate_square_space(str, map);
	while (str[i])
	{
		tmp[i] = malloc(map->map_x + 1);
		tmp[i][map->map_x] = 0;
		j = 0;
		k = 0;
		while (j < map->map_x)
		{
			tmp[i][j] = ' ';
			if (str[i][k])
				tmp[i][j] = str[i][k++];
			j++;
		}
		i++;
	}
	map->map_x = map->map_x * TILE;
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
	str = square_format(str, map);
	flag = check_map_validation(str, &i);
	if (flag != 1)
		return (free(map), handle_map_error(flag), NULL);
	new = NULL;
	i = 0;
	flag = 0;
	while (str[i])
	{
		new = join_optclean(new, str[i], 1);
		new = join_optclean(new, "\n", 1);
		i++;
	}
	map->map = new;
	get_player_position(map, str);
	return (ft_free(str), map);
}
