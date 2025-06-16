/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:52:41 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/16 10:04:30 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <X11/keysym.h>

int	handle_key_down(int keycode, t_keys *keys)
{
	if (keycode == XK_Escape)
		keys->escape = 1;
	else if (keycode == XK_w)
		keys->w = 1;
	else if (keycode == XK_s)
		keys->s = 1;
	else if (keycode == XK_a)
		keys->a = 1;
	else if (keycode == XK_d)
		keys->d = 1;
	return (0);
}

int	handle_key_up(int keycode, t_keys *keys)
{
	if (keycode == XK_Escape)
		keys->escape = 0;
	else if (keycode == XK_w)
		keys->w = 0;
	else if (keycode == XK_s)
		keys->s = 0;
	else if (keycode == XK_a)
		keys->a = 0;
	else if (keycode == XK_d)
		keys->d = 0;
	return (0);
}

void	handle_input(t_keys *const keys, t_camera *const camera,
	void *const mlx)
{
	const t_vec2	dir = {keys->a - keys->d, keys->w - keys->s};

	if (keys->escape)
		mlx_loop_end(mlx);
	camera->position.x += dir.x * -camera->cos.y + dir.y * camera->sin.y;
	camera->position.y += dir.x * camera->sin.y + dir.y * camera->cos.y;
}
