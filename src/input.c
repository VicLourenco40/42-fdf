/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:52:41 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/16 11:32:03 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <X11/keysym.h>
#include <math.h>

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
	else if (keycode == XK_Up)
		keys->up = 1;
	else if (keycode == XK_Down)
		keys->down = 1;
	else if (keycode == XK_Left)
		keys->left = 1;
	else if (keycode == XK_Right)
		keys->right = 1;
	else if (keycode == XK_minus)
		keys->minus = 1;
	else if (keycode == XK_equal)
		keys->plus = 1;
	else if (keycode == XK_bracketleft)
		keys->lbracket = 1;
	else if (keycode == XK_bracketright)
		keys->rbracket = 1;
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
	else if (keycode == XK_Up)
		keys->up = 0;
	else if (keycode == XK_Down)
		keys->down = 0;
	else if (keycode == XK_Left)
		keys->left = 0;
	else if (keycode == XK_Right)
		keys->right = 0;
	else if (keycode == XK_minus)
		keys->minus = 0;
	else if (keycode == XK_equal)
		keys->plus = 0;
	else if (keycode == XK_bracketleft)
		keys->lbracket = 0;
	else if (keycode == XK_bracketright)
		keys->rbracket = 0;
	return (0);
}

void	handle_input(t_keys *const keys, t_camera *const camera,
	void *const mlx)
{
	const t_vec2	dir = {keys->d - keys->a, keys->w - keys->s};

	if (keys->escape)
		mlx_loop_end(mlx);
	camera->rotation.x = ft_clampf(\
		camera->rotation.x + (keys->down - keys->up) * 0.01f, \
		0.0f, M_PI_2);
	camera->rotation.y += (keys->right - keys->left) * 0.01f + \
		((camera->rotation.y > 2 * M_PI) * -2 * M_PI) + \
		((camera->rotation.y < -2 * M_PI) * 2 * M_PI);
	camera->sin = (t_vec2f){sinf(camera->rotation.x), sinf(camera->rotation.y)};
	camera->cos = (t_vec2f){cosf(camera->rotation.x), cosf(camera->rotation.y)};
	camera->position.x += dir.x * camera->sin.y + dir.y * camera->cos.y;
	camera->position.y += dir.x * -camera->cos.y + dir.y * camera->sin.y;
	camera->zoom = ft_clampf(camera->zoom + (keys->plus - keys->minus) * 0.1f, \
		1.0f, 50.0f);
	camera->height_scale = ft_clampf(\
		camera->height_scale + (keys->rbracket - keys->lbracket) * 0.01f, \
		0.0f, 5.0f);
}
