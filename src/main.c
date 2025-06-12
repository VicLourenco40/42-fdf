/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/12 11:11:46 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <stdlib.h>
#include <math.h>

int	handle_key(const int keycode, t_state *const state)
{
	const float	mag = 2.0f;

	//ft_printf("%d\n", keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(state->mlx.ptr);
	else if (keycode == KEY_W)
	{
		state->camera.position.x += mag * cosf(state->camera.rotation.y);
		state->camera.position.y += mag * sinf(state->camera.rotation.y);
	}
	else if (keycode == KEY_S)
	{
		state->camera.position.x -= mag * cosf(state->camera.rotation.y);
		state->camera.position.y -= mag * sinf(state->camera.rotation.y);
	}
	else if (keycode == KEY_A)
	{
		state->camera.position.x += mag * -sinf(state->camera.rotation.y);
		state->camera.position.y += mag * cosf(state->camera.rotation.y);
	}
	else if (keycode == KEY_D)
	{
		state->camera.position.x -= mag * -sinf(state->camera.rotation.y);
		state->camera.position.y -= mag * cosf(state->camera.rotation.y);
	}
	else if (keycode == KEY_UP)
		state->camera.rotation.x += asinf(tanf(M_PI / 6)) / 4;
	else if (keycode == KEY_DOWN)
		state->camera.rotation.x -= asinf(tanf(M_PI / 6)) / 4;
	else if (keycode == KEY_LEFT)
		state->camera.rotation.y -= M_PI_4 / 4;
	else if (keycode == KEY_RIGHT)
		state->camera.rotation.y += M_PI_4 / 4;
	else if (keycode == KEY_PLUS)
		state->camera.zoom = \
			ft_clampf(state->camera.zoom + 4.0f, 4.0f, 80.0f);
	else if (keycode == KEY_MINUS)
		state->camera.zoom = \
			ft_clampf(state->camera.zoom - 4.0f, 4.0f, 80.0f);
	else if (keycode == KEY_SQ_BRACKET_LEFT)
		state->camera.height_scale = \
			ft_clampf(state->camera.height_scale - 0.1f, 0.0f, 10.0f);
	else if (keycode == KEY_SQ_BRACKET_RIGHT)
		state->camera.height_scale = \
			ft_clampf(state->camera.height_scale + 0.1f, 0.0f, 10.0f);
	return (0);
}

static int	loop(t_state *const state)
{
	project_map(&state->map, &state->camera, &state->mlx);
	return (0);
}

static bool	init_state(const char *const file, t_state *const state)
{
	ft_bzero(state, sizeof(t_state));
	parse_map(file, &state->map);
	if (!state->map.points)
		return (false);
	init_mlx(&state->mlx);
	if (!state->mlx.ptr)
		return (false);
	init_camera(&state->camera, state->mlx.ptr, state->map.size);
	if (!state->camera.points)
		return (false);
	return (true);
}

void	free_state(t_state *const state)
{
	free_map(&state->map);
	free_camera(&state->camera, state->mlx.ptr);
	free_mlx(&state->mlx);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc < 2)
	{
		ft_putstr_fd("usage: fdf <file>\n", 1);
		return (1);
	}
	if (!init_state(argv[1], &state))
	{
		ft_putstr_fd("fdf: initialization error\n", 2);
		free_state(&state);
		return (1);
	}
	mlx_key_hook(state.mlx.win_ptr, &handle_key, (void *) &state);
	mlx_loop_hook(state.mlx.ptr, &loop, (void *) &state);
	mlx_loop(state.mlx.ptr);
	free_state(&state);
}
