/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:13:31 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 14:59:14 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <math.h>
#include <stdlib.h>

void	reset_camera(t_camera *const camera, const t_vec2 map_size)
{
	camera->position = (t_vec2f){
		-(map_size.x - 1) / 2.0f, -(map_size.y - 1) / 2.0f};
	camera->rotation = (t_vec2f){asinf(tanf(M_PI / 6)), -M_PI_4};
}

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
	reset_camera(camera, size);
	while (--size.x)
		camera->points[size.x] = camera->points[0] + (size.x * size.y);
	camera->image.data = (t_color *) mlx_get_data_addr(camera->image.ptr, \
		&camera->image.color_depth, &camera->image.line_size, \
		&camera->image.endian);
	camera->image.line_size /= sizeof(t_color);
	camera->zoom = 4.0f;
	camera->height = 0.5f;
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

static t_vec2	point_to_camera(const t_camera *const camera, t_vec3f point)
{
	const t_vec2f	sin = camera->sin;
	const t_vec2f	cos = camera->cos;
	t_vec2			pixel;

	point.x += camera->position.x;
	point.y += camera->position.y;
	pixel.x = roundf(WINDOW_WIDTH / 2.0f + \
		camera->zoom * (cos.y * point.y - sin.y * point.x));
	pixel.y = roundf(WINDOW_HEIGHT / 2.0f + \
		camera->zoom * (cos.x * (sin.y * point.y + cos.y * point.x) - \
		sin.x * point.z * camera->height));
	return (pixel);
}

void	map_to_camera(const t_map *const map, t_camera *const camera)
{
	t_vec2	c;

	c.x = -1;
	while (++c.x < map->size.x)
	{
		c.y = -1;
		while (++c.y < map->size.y)
			camera->points[c.x][c.y] = point_to_camera(camera, \
				(t_vec3f){c.x, c.y, map->points[c.x][c.y]});
	}
}
