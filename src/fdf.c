/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/05/27 14:28:16 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>

int	free_exit(int keycode, void **param)
{
	mlx_destroy_window(*param, *(param - 1));
	mlx_destroy_display(*param);
	free(*param);
	exit(0);
}

int	foo(void *param)
{
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 640, 480, "fdf");
	if (!win_ptr)
		return (1);
	mlx_pixel_put(mlx_ptr, win_ptr, 8, 8, 0xFFFFFFFF);
	mlx_loop_hook(mlx_ptr, &foo, NULL);
	mlx_key_hook(win_ptr, &free_exit, &mlx_ptr);
	mlx_loop(mlx_ptr);
}
