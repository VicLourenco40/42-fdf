/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:41:59 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 17:31:35 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <math.h>

static bool	is_point_oob(const t_vec2 point)
{
	return (point.x < 0 || point.y < 0 || point.x >= WINDOW_WIDTH || \
		point.y >= WINDOW_HEIGHT);
}

void	put_image_pixel(t_image *const image, const t_vec2 point)
{
	if (is_point_oob(point))
		return ;
	((int *)(image->data + point.y * image->line_size))[point.x] = -1;
}

void	put_image_line(t_image *const image, const t_vec2 p1, const t_vec2 p2)
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
			roundf(p1.y + step.y * i)});
}
