/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:26:13 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 17:46:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (flag == -8)
		printf("\e[31m>> [PARSING ERORR] bad element!\e[0m \n");
	else if (flag == -7)
		printf("\e[31m>> [PARSING ERORR] Unknown enemy position!\e[0m \n");
	else if (flag == -6)
		printf("\e[31m>> [PARSING ERORR] Illogical door placment!\e[0m \n");
	else if (flag == -5)
		printf("\e[31m>> [TEXTURE ERORR] Only .xpm file!\e[0m \n");
	else if (flag == -4)
		printf("\e[31m>> [PARSING ERORR] Double or Missing elements!\e[0m \n");
	else if (flag == -3)
		printf("\e[31m>> [PARSING ERORR] Map data not found!\e[0m \n");
	else if (flag == -2)
		printf("\e[31m>> [PARSING ERORR] Empty line in map!\e[0m \n");
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
		if (ft_strlen(str[i]) > (size_t)map->map_x)
			map->map_x = ft_strlen(str[i]);
		i++;
	}
	map->map_y = i;
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
	map->map_x = map->map_x;
	return (tmp);
}

t_game	*get_map(char **str, char *content, t_game *map)
{
	int		i;
	int		flag;
	char	*tmp;

	i = 0;
	tmp = ft_strnstr(content, str[0], ft_strlen(content));
	if (ft_strnstr(tmp, "\n\n", ft_strlen(tmp)))
		return (free_map(map), handle_map_error(-2), NULL);
	str = square_format(str, map);
	flag = check_map_validation(str, &i);
	map->map = str;
	if (flag != 1 || check_door_logic(str, &flag))
		return (free_map(map), handle_map_error(flag), NULL);
	get_player_position(map);
	if (get_enemy_position(map) != 1)
		return (free_map(map), handle_map_error(0), NULL);
	return (map);
}
