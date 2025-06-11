/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:41:59 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 12:27:53 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <math.h>

void	put_image_pixel(t_image *const image, const t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || \
		pos.x >= WINDOW_WIDTH || pos.y >= WINDOW_HEIGHT)
		return ;
	((int *)(image->data + pos.y * image->line_size))[pos.x] = 0xFFFFFFFF;
}

void	put_image_line(t_image *const image, const t_vec2 p1, const t_vec2 p2)
{
	const t_vec2	delta = {p2.x - p1.x, p2.y - p1.y};
	const int		step = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	float			step_x;
	float			step_y;
	int				i;

	put_image_pixel(image, p1);
	if (step == 0)
		return ;
	step_x = (float)delta.x / step;
	step_y = (float)delta.y / step;
	i = 0;
	while (++i <= step)
		put_image_pixel(image, \
				(t_vec2){roundf(p1.x + step_x * i), roundf(p1.y + step_y * i)});
}
