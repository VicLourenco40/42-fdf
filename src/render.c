/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:06:14 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 09:53:19 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

void	render_map(const t_map *const map, t_camera *const camera,
	t_mlx *const mlx)
{
	const t_vec2	i = {ft_signf(camera->cos.y), ft_signf(camera->sin.y)};
	t_vec2			c;

	c.x = (i.x < 0) * (map->size.x - 1);
	while (c.x >= 0 && c.x < map->size.x)
	{
		c.y = (i.y < 0) * (map->size.y - 1);
		while (c.y >= 0 && c.y < map->size.y)
		{
			if (c.x == 0 && c.y == 0)
				put_image_pixel(&camera->image, camera->points[0][0],
					map->colors[0][0]);
			if (c.x)
				put_image_line(&camera->image, (t_line){\
					{camera->points[c.x][c.y], camera->points[c.x - 1][c.y]}, \
					{map->colors[c.x][c.y], map->colors[c.x - 1][c.y]}});
			if (c.y)
				put_image_line(&camera->image, (t_line){\
					{camera->points[c.x][c.y], camera->points[c.x][c.y - 1]}, \
					{map->colors[c.x][c.y], map->colors[c.x][c.y - 1]}});
			c.y += i.y;
		}
		c.x += i.x;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, camera->image.ptr, 0, 0);
}
