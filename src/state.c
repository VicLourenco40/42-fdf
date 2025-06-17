/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:28:00 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 12:26:01 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	get_map_desc(char *desc, const char *const file,
	const t_vec2 size)
{
	desc += ft_strlcpy(desc, file, 288);
	desc += ft_strlcpy(desc, " (", 288);
	desc += ft_itoa_cpy(desc, size.x);
	desc += ft_strlcpy(desc, "x", 288);
	desc += ft_itoa_cpy(desc, size.y);
	ft_strlcpy(desc, ")", 288);
}

bool	init_state(const char *const file, t_state *const state)
{
	ft_bzero(state, sizeof(t_state));
	parse_map(file, &state->map);
	if (!state->map.points)
		return (false);
	get_map_desc(state->map_desc, file, state->map.size);
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
