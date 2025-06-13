/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:13:31 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/13 12:12:26 by vde-albu         ###   ########.fr       */
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
	camera->image.data = (t_color *) mlx_get_data_addr(camera->image.ptr, \
		&camera->image.color_depth, &camera->image.line_size, \
		&camera->image.endian);
	camera->image.line_size /= sizeof(t_color);
	camera->rotation = (t_vec2f){asinf(tanf(M_PI / 6)), M_PI_4};
	camera->sin = (t_vec2f){sinf(camera->rotation.x), sinf(camera->rotation.y)};
	camera->cos = (t_vec2f){cosf(camera->rotation.x), cosf(camera->rotation.y)};
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

static t_vec2	point_to_camera(const t_camera *const camera, t_vec3f point)
{
	const t_vec2f	sin = camera->sin;
	const t_vec2f	cos = camera->cos;
	t_vec2			pixel;

	point.x += camera->position.x;
	point.y += camera->position.y;
	pixel.x = roundf(WINDOW_WIDTH / 2.0f + camera->zoom * \
		(cos.y * point.y - sin.y * point.x));
	pixel.y = roundf(WINDOW_HEIGHT / 2.0f + camera->zoom * \
		(cos.x * (sin.y * point.y + cos.y * point.x) - \
		sin.x * point.z * camera->height_scale));
	return (pixel);
}

static void	map_to_camera(const t_map *const map, t_camera *const camera)
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

void	draw_map(const t_map *const map, t_camera *const camera,
	t_mlx *const mlx)
{
	const t_vec2	i = {ft_signf(camera->cos.y), ft_signf(camera->sin.y)};
	t_vec2			c;

	ft_bzero(camera->image.data,
		WINDOW_HEIGHT * sizeof(t_color) * camera->image.line_size);
	map_to_camera(map, camera);
	c.x = (i.x < 0) * (map->size.x - 2);
	while ((i.x > 0 && c.x < map->size.x) || (i.x < 0 && c.x >= 0))
	{
		c.y = (i.y < 0) * (map->size.y - 2);
		while ((i.y > 0 && c.y < map->size.y) || (i.y < 0 && c.y >= 0))
		{
			if (c.x)
				put_image_line(&camera->image,
					camera->points[c.x][c.y], map->colors[c.x][c.y],
					camera->points[c.x - 1][c.y], map->colors[c.x - 1][c.y]);
			if (c.y)
				put_image_line(&camera->image,
					camera->points[c.x][c.y], map->colors[c.x][c.y],
					camera->points[c.x][c.y - 1], map->colors[c.x][c.y - 1]);
			c.y += i.y;
		}
		c.x += i.x;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, camera->image.ptr, 0, 0);
}
