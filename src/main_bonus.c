/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 14:39:07 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf_bonus.h>
#include <mlx.h>

#include <stdlib.h>
#include <X11/X.h>

static int	loop(t_state *const state)
{
	handle_movement(&state->keys, &state->camera);
	clear_image(&state->camera.image);
	map_to_camera(&state->map, &state->camera);
	render_map(&state->mlx, &state->map, &state->camera);
	render_overlay(&state->mlx, state->map_desc);
	return (0);
}

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc != 2)
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
	mlx_hook(state.mlx.win_ptr, KeyPress, KeyPressMask, handle_key, &state);
	mlx_hook(state.mlx.win_ptr, KeyRelease, KeyReleaseMask, handle_key_up,
		&state.keys);
	mlx_hook(state.mlx.win_ptr, ClientMessage, LeaveWindowMask, mlx_loop_end,
		state.mlx.ptr);
	mlx_loop_hook(state.mlx.ptr, loop, &state);
	mlx_loop(state.mlx.ptr);
	free_state(&state);
}
