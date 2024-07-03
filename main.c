/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:51:20 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/03 22:32:28 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_hook(int keycode, void *param)
{
    printf("Key pressed: %d\n", keycode);
    
    if (keycode == 65307)
        mlx_loop_end(param);
    
    return 0;
}

int	main()
{
	void *mlx_ptr = mlx_init();
	void *mlx_win = mlx_new_window(mlx_ptr, 500, 500, "cub3D");
	mlx_key_hook(mlx_win, key_hook, mlx_ptr);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, mlx_win);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
