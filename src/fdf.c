/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/04 10:13:07 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

int	free_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

int	key_handler(int keycode, void *param)
{
	if (keycode == ESCAPE)
		free_exit(param);
	return (0);
}

int	loop(void)
{
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	if (!mlx.ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.ptr, 640, 480, "fdf");
	if (!mlx.win_ptr)
		return (1);
	mlx_key_hook(mlx.win_ptr, &key_handler, &mlx);
	mlx_loop_hook(mlx.ptr, &loop, NULL);
	mlx_loop(mlx.ptr);
}
