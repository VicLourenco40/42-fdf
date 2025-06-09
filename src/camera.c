/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:13:31 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 19:23:40 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <math.h>

static t_vec2	map_to_camera(const t_camera *const camera, t_vec3 point)
{
	const float	sina = sinf(camera->rotation.x);
	const float	cosa = cosf(camera->rotation.x);
	const float	sinb = sinf(camera->rotation.y);
	const float	cosb = cosf(camera->rotation.y);

	point.x = (point.x + camera->position.x) * camera->zoom;
	point.y = (point.y + camera->position.y) * camera->zoom;
	point.z *= camera->height_scale * camera->zoom;
	return ((t_vec2){(cosb * point.x) - (sinb * point.y), \
		(cosa * ((sinb * point.x) + (cosb * point.y))) - (sina * point.z)});
}

void	project_map(t_map *map, t_camera *camera, t_mlx *mlx)
{
	int	x;
	int	y;

	clear_image(&camera->image);
	x = -1;
	while (++x < map->size.x)
	{
		y = -1;
		while (++y < map->size.y)
		{
			camera->points[x][y] = map_to_camera(camera, \
				(t_vec3){y, x, map->points[x][y]});
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
