/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:58:02 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 19:30:47 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>
#include <math.h>

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
	}
}

void	init_camera(t_camera *const camera, void *mlx, t_vec2 size)
{
	ft_bzero(camera, sizeof(t_camera));
	camera->points = ft_calloc(size.x, sizeof(t_vec2 *));
	if (!camera->points)
		return ;
	camera->points[0] = ft_calloc(size.x * size.y, sizeof(t_vec2));
	camera->image.ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!camera->points[0] || !camera->image.ptr)
	{
		free(camera->points);
		camera->points = NULL;
		return ;
	}
	while (--size.x)
		camera->points[size.x] = camera->points[0] + (size.x * size.y);
	camera->image.data = mlx_get_data_addr(camera->image.ptr, \
		&camera->image.color_depth, &camera->image.line_size, \
		&camera->image.endian);
	camera->rotation = (t_vec2f){asinf(tanf(M_PI / 6)), M_PI_4};
	camera->zoom = 20.0f;
	camera->height_scale = 1.0f;
}
