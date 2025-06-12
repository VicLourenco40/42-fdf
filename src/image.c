/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:41:59 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/12 13:10:39 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <math.h>

static bool	is_point_oob(const t_vec2 point)
{
	return (point.x < 0 || point.y < 0 || point.x >= WINDOW_WIDTH || \
		point.y >= WINDOW_HEIGHT);
}

static t_color	color_lerp(const t_color c1, const t_color c2, const float t)
{
	return ((t_color){
		c1.b + (c2.b - c1.b) * t,
		c1.g + (c2.g - c1.g) * t,
		c1.r + (c2.r - c1.r) * t,
		0});
}

void	put_image_pixel(t_image *const image, const t_vec2 point,
	const t_color color)
{
	if (is_point_oob(point))
		return ;
	image->data[point.x + point.y * image->line_size] = color;
}

void	put_image_line(t_image *const image, const t_vec2 p1, const t_color c1,
	const t_vec2 p2, const t_color c2)
{
	const t_vec2	delta = {p2.x - p1.x, p2.y - p1.y};
	const int		steps = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	const t_vec2f	step = (t_vec2f){(float)delta.x / steps,
		(float)delta.y / steps};
	int				i;

	if (is_point_oob(p1) && is_point_oob(p2))
		return ;
	i = -1;
	while (++i <= steps)
		put_image_pixel(image, (t_vec2){
			roundf(p1.x + step.x * i),
			roundf(p1.y + step.y * i)},
			color_lerp(c1, c2, (float)i / steps));
}
