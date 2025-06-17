/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:58:02 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 10:25:00 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <stdlib.h>

void	init_mlx(t_mlx *const mlx)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return ;
	mlx->win_ptr = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (!mlx->win_ptr)
		free_mlx(mlx);
}

void	free_mlx(t_mlx *const mlx)
{
	if (mlx->ptr)
	{
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
	}
	ft_bzero(mlx, sizeof(t_mlx));
}
