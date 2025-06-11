/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:13:31 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 12:27:43 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <math.h>
#include <stdlib.h>

void	init_camera(t_camera *const camera, void *mlx, t_vec2 size)
{
	camera->points = ft_calloc(size.x, sizeof(t_vec2 *));
	if (!camera->points)
		return ;
	camera->points[0] = ft_calloc(size.x * size.y, sizeof(t_vec2));
	if (!camera->points[0])
		return (free_camera(camera, mlx));
	camera->image.ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!camera->image.ptr)
		return (free_camera(camera, mlx));
	camera->position = (t_vec2f){-size.x / 2.0f, -size.y / 2.0f};
	while (--size.x)
		camera->points[size.x] = camera->points[0] + (size.x * size.y);
	camera->image.data = mlx_get_data_addr(camera->image.ptr, \
		&camera->image.color_depth, &camera->image.line_size, \
		&camera->image.endian);
	camera->rotation = (t_vec2f){asinf(tanf(M_PI / 6)), M_PI_4};
	camera->zoom = 12.0f;
	camera->height_scale = 1.0f;
}

void	free_camera(t_camera *const camera, void *mlx)
{
	if (camera->points)
	{
		free(camera->points[0]);
		free(camera->points);
	}
	if (camera->image.ptr && mlx)
		mlx_destroy_image(mlx, camera->image.ptr);
	ft_bzero(camera, sizeof(camera));
}

static t_vec2	map_to_camera(const t_camera *const camera, t_vec3f point)
{
	const float	sina = sinf(camera->rotation.x);
	const float	cosa = cosf(camera->rotation.x);
	const float	sinb = sinf(camera->rotation.y);
	const float	cosb = cosf(camera->rotation.y);

	point = (t_vec3f){
		(point.x + camera->position.x) * camera->zoom,
		(point.y + camera->position.y) * camera->zoom,
		point.z * camera->height_scale * camera->zoom};
	return ((t_vec2){
		roundf(WINDOW_WIDTH / 2.0f + \
			cosb * point.y - sinb * point.x),
		roundf(WINDOW_HEIGHT / 2.0f + \
			cosa * (sinb * point.y + cosb * point.x) - sina * point.z)});
}

void	project_map(const t_map *const map, t_camera *const camera, \
	t_mlx *const mlx)
{
	int	x;
	int	y;

	ft_bzero(camera->image.data, camera->image.line_size * WINDOW_HEIGHT);
	x = -1;
	while (++x < map->size.x)
	{
		y = -1;
		while (++y < map->size.y)
		{
			camera->points[x][y] = map_to_camera(camera, \
				(t_vec3f){x, y, map->points[x][y]});
			if (x)
				put_image_line(&camera->image, camera->points[x][y], \
					camera->points[x - 1][y]);
			if (y)
				put_image_line(&camera->image, camera->points[x][y], \
					camera->points[x][y - 1]);
		}
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, camera->image.ptr, 0, 0);
}
