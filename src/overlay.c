/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:07:19 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 12:30:27 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

static inline void	put_window_string(const t_mlx *const mlx, int x, int y,
	const char *const string)
{
	mlx_string_put(mlx->ptr, mlx->win_ptr, x, y, 0xFFFFFFFF, (char *) string);
}

void	render_overlay(const t_mlx *const mlx, const char *const map_desc)
{
	put_window_string(mlx, 8, 16, "vde-albu's FDF");
	put_window_string(mlx, 8, 48, "Movement: W A S D");
	put_window_string(mlx, 8, 64, "Rotation: Arrow Keys");
	put_window_string(mlx, 8, 80, "Zoom: - +");
	put_window_string(mlx, 8, 96, "Height: [ ]");
	put_window_string(mlx, 8, 112, "View Presets: Keypad");
	put_window_string(mlx, 8, WINDOW_HEIGHT - 8, map_desc);
}
