/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:15:13 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 18:54:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			ft_free(map->map);
		free(map);
	}
}
