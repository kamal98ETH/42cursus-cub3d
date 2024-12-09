/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:48:47 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 17:46:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	isthere(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	array_size(char const *s, char *c)
{
	size_t	len;

	len = 1;
	while (*s)
	{
		if (!isthere(c, *s))
		{
			len++;
			while (*s && !isthere(c, *s))
				s++;
		}
		if (*s)
			s++;
	}
	return (len);
}

static void	free_array(char **array)
{
	size_t	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static char	**fill_array(char **array, char const *s, char *c)
{
	size_t	index;
	char	*start;

	index = 0;
	while (*s)
	{
		if (!isthere(c, *s))
		{
			start = (char *)s;
			while (*s && !isthere(c, *s))
				s++;
			array[index] = ft_substr(start, 0, s - start);
			if (!array[index])
			{
				free_array(array);
				return (NULL);
			}
			index++;
		}
		if (*s)
			s++;
	}
	array[index] = 0;
	return (array);
}

char	**multi_split(char const *s, char *c)
{
	char	**array;
	size_t	array_len;

	if (!s)
		return (NULL);
	array_len = array_size(s, c);
	array = (char **)malloc(array_len * sizeof(char *));
	if (!array)
		return (NULL);
	array = fill_array(array, s, c);
	return (array);
}
