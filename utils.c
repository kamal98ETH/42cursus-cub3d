/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:08:42 by laoubaid          #+#    #+#             */
/*   Updated: 2024/09/18 17:25:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_whitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	valid_chars(int c)
{
	if (c == '1' || c == '0' || c == 'S' \
		|| c == 'W' || c == 'N' || c == 'E')
		return (1);
	return (0);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*join_optclean(char *s1, char *s2, int flag)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	tmp = s1;
	if (!s1 && !s2)
		return (0);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	if (s1)
		while (*s1)
			join[i++] = *s1++;
	s1 = s2;
	if (s2)
		while (*s2)
			join[i++] = *s2++;
	if (flag == 1 || flag == 3)
		free(tmp);
	if (flag == 2 || flag == 3)
		free(s1);
	return (join[i] = 0, join);
}

int	unique_atoi(const char *str, int *flag)
{
	int	num;

	num = 0;
	while(*str == '0')
		str++;
	if (ft_strlen(str) > 3)
		return (*flag = 1, -1);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
	}
	if (num > 255 || *str)
		return (*flag = 1, -1);
	return (num);
}
