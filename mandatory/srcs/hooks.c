/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:55:17 by laoubaid          #+#    #+#             */
/*   Updated: 2024/12/08 18:54:57 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook_press(int keycode, t_val *val)
{
	if (keycode == ESC_KEYCODE)
		mlx_loop_end(val->mlx_ptr);
	if (keycode == W_KEYCODE)
		val->keys[W_K] = 1;
	if (keycode == S_KEYCODE)
		val->keys[S_K] = 1;
	if (keycode == A_KEYCODE)
		val->keys[A_K] = 1;
	if (keycode == D_KEYCODE)
		val->keys[D_K] = 1;
	if (keycode == LA_KEYCODE)
		val->keys[LA_K] = 1;
	if (keycode == RA_KEYCODE)
		val->keys[RA_K] = 1;
	return (0);
}

int	key_hook_release(int keycode, t_val *val)
{
	if (keycode == W_KEYCODE)
		val->keys[W_K] = 0;
	if (keycode == S_KEYCODE)
		val->keys[S_K] = 0;
	if (keycode == A_KEYCODE)
		val->keys[A_K] = 0;
	if (keycode == D_KEYCODE)
		val->keys[D_K] = 0;
	if (keycode == LA_KEYCODE)
		val->keys[LA_K] = 0;
	if (keycode == RA_KEYCODE)
		val->keys[RA_K] = 0;
	return (0);
}

int	ft_close(t_val *val)
{
	mlx_loop_end(val->mlx_ptr);
	return (0);
}

void	mlx_hooks(t_val *val)
{
	mlx_hook(val->win_ptr, 17, 0, ft_close, val);
	mlx_hook(val->win_ptr, KeyPress, KeyPressMask, key_hook_press, val);
	mlx_hook(val->win_ptr, KeyRelease, KeyReleaseMask, key_hook_release, val);
}
