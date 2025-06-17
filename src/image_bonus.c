/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:41:59 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 14:07:49 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf_bonus.h>

#include <math.h>

static bool	is_point_oob(const t_vec2 point)
{
	return (point.x < 0 || point.y < 0 || \
		point.x >= WINDOW_WIDTH || point.y >= WINDOW_HEIGHT);
}

static t_color	color_lerp(const t_color c1, const t_color c2, const float t)
{
	return ((t_color){
		c1.b + (c2.b - c1.b) * t,
		c1.g + (c2.g - c1.g) * t,
		c1.r + (c2.r - c1.r) * t,
		0
	});
}

void	put_image_pixel(t_image *const image, const t_vec2 point,
	const t_color color)
{
	if (is_point_oob(point))
		return ;
	image->data[point.x + point.y * image->line_size] = color;
}

void	put_image_line(t_image *const image, const t_line line)
{
	const t_vec2	delta = {
		line.points[1].x - line.points[0].x,
		line.points[1].y - line.points[0].y};
	const int		steps = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	const t_vec2f	step = {(float)delta.x / steps, (float)delta.y / steps};
	int				i;
	t_vec2			point;

	if (is_point_oob(line.points[0]) && is_point_oob(line.points[1]))
		return ;
	i = -1;
	while (++i <= steps)
	{
		point.x = roundf(line.points[0].x + step.x * i);
		point.y = roundf(line.points[0].y + step.y * i);
		put_image_pixel(image, point,
			color_lerp(line.colors[0], line.colors[1], (float)i / steps));
	}
}

void	clear_image(t_image *const image)
{
	ft_bzero(image->data, WINDOW_HEIGHT * sizeof(t_color) * image->line_size);
}
