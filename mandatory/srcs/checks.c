/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:02:42 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 18:54:40 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_name(char	*str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i >= 0)
	{
		if (str[i] == '.' && !ft_strncmp(str + i, ".cub", 5))
			return (1);
		else if (str[i] == '.')
			return (0);
		i--;
	}
	return (0);
}

int	coma_check(char *str)
{
	int	i;
	int	count;
	int	save;

	i = 0;
	count = 0;
	save = 0;
	while (str[i])
	{
		if (str[i] == ',' && save == 0)
		{
			count++;
			save = 1;
		}
		else if (str[i] == ',')
			return (1);
		else if (save)
			save = 0;
		i++;
		while (str[i] && is_whitespace(str[i]))
			i++;
	}
	if (count > 2)
		return (1);
	return (0);
}

int	check_map_validation(char **s, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	while (s[*i])
	{
		j = 0;
		while (s[*i][j])
		{
			if (s[*i][j] == 'S' || s[*i][j] == 'W' || s[*i][j] == 'N'
				|| s[*i][j] == 'E' || s[*i][j] == '0')
			{
				if (!(*i && valid(s[*i - 1][j]) && j && valid(s[*i][j - 1]) \
				&& s[*i + 1] && valid(s[*i + 1][j]) && valid(s[*i][j + 1])))
					return (-1);
				if (s[*i][j] != '0')
					flag++;
			}
			else if (s[*i][j] != '1' && s[*i][j] != ' ' && s[*i][j] != '2')
				return (flag);
			j++;
		}
		(*i)++;
	}
	return (flag);
}

int	check_if_map(char *str)
{
	char	**elems;

	elems = multi_split(str, "\t\n\v\f\r ,");
	if (elems[0] && !ft_strncmp(elems[0], "C", 2))
		return (ft_free(elems), 0);
	else if (elems[0] && !ft_strncmp(elems[0], "F", 2))
		return (ft_free(elems), 0);
	else if (elems[0] && !ft_strncmp(elems[0], "NO", 3))
		return (ft_free(elems), 0);
	else if (elems[0] && !ft_strncmp(elems[0], "SO", 3))
		return (ft_free(elems), 0);
	else if (elems[0] && !ft_strncmp(elems[0], "EA", 3))
		return (ft_free(elems), 0);
	else if (elems[0] && !ft_strncmp(elems[0], "WE", 3))
		return (ft_free(elems), 0);
	return (ft_free(elems), 1);
}
