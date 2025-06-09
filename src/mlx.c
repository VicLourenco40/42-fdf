/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:58:02 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 13:02:34 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>

void	init_mlx(t_mlx *const mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return ;
	mlx->win_ptr = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		mlx->ptr = NULL;
		return ;
	}
	mlx->image.ptr = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->image.ptr)
	{
		mlx_destroy_window(mlx->ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		ft_bzero(mlx, sizeof(t_mlx));
		return ;
	}
	mlx->image.data = mlx_get_data_addr(mlx->image.ptr, \
		&mlx->image.color_depth, &mlx->image.line_size, &mlx->image.endian);
}
