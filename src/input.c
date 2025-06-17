/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:52:41 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 12:29:34 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <X11/keysym.h>
#include <math.h>

void	handle_movement(t_keys *const keys, t_camera *const camera)
{
	const t_vec2	dir = {keys->d - keys->a, keys->w - keys->s};

	camera->rotation.x = ft_clampf(\
		camera->rotation.x + (keys->down - keys->up) * 0.02f, \
		0.0f, M_PI_2);
	camera->rotation.y += (keys->right - keys->left) * 0.02f + \
		((camera->rotation.y > 2 * M_PI) * -2 * M_PI) + \
		((camera->rotation.y < -2 * M_PI) * 2 * M_PI);
	camera->sin = (t_vec2f){sinf(camera->rotation.x), sinf(camera->rotation.y)};
	camera->cos = (t_vec2f){cosf(camera->rotation.x), cosf(camera->rotation.y)};
	camera->position.x += dir.x * camera->sin.y + dir.y * camera->cos.y;
	camera->position.y += dir.x * -camera->cos.y + dir.y * camera->sin.y;
	camera->zoom = ft_clampf(\
		camera->zoom + (keys->plus - keys->minus) * camera->zoom * 0.01f, \
		1.0f, 50.0f);
	camera->height = ft_clampf(\
		camera->height + (keys->rbracket - keys->lbracket) * 0.01f, \
		0.0f, 5.0f);
}

static void	handle_projections(const int keycode, t_camera *const camera,
	const t_vec2 map_size)
{
	const float		x_angle = asinf(tanf(M_PI / 6));

	if (keycode >= XK_KP_Home && keycode <= XK_KP_Begin)
		reset_camera(camera, map_size);
	if (keycode == XK_KP_Home)
		camera->rotation = (t_vec2f){x_angle, -M_PI_2 - M_PI_4};
	else if (keycode == XK_KP_Up)
		camera->rotation = (t_vec2f){M_PI_2, M_PI};
	else if (keycode == XK_KP_Page_Up)
		camera->rotation = (t_vec2f){x_angle, M_PI_2 + M_PI_4};
	else if (keycode == XK_KP_Left)
		camera->rotation = (t_vec2f){M_PI_2, -M_PI_2};
	else if (keycode == XK_KP_Begin)
		camera->rotation = (t_vec2f){0, 0};
	else if (keycode == XK_KP_Right)
		camera->rotation = (t_vec2f){M_PI_2, M_PI_2};
	else if (keycode == XK_KP_End)
		camera->rotation = (t_vec2f){x_angle, -M_PI_4};
	else if (keycode == XK_KP_Down)
		camera->rotation = (t_vec2f){M_PI_2, 0};
	else if (keycode == XK_KP_Page_Down)
		camera->rotation = (t_vec2f){x_angle, M_PI_4};
}

static void	handle_key_down(const int keycode, t_keys *const keys)
{
	if (keycode == XK_w)
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
}

int	handle_key_up(const int keycode, t_keys *const keys)
{
	if (keycode == XK_w)
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

int	handle_key(const int keycode, t_state *const state)
{
	if (keycode == XK_Escape)
		mlx_loop_end(state->mlx.ptr);
	handle_projections(keycode, &state->camera, state->map.size);
	handle_key_down(keycode, &state->keys);
	return (0);
}
