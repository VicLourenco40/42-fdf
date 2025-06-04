/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/04 13:12:43 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>
#include <stdlib.h>
#include <math.h>

int	free_exit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}

int	key_handler(int keycode, void *param)
{
	if (keycode == ESCAPE)
		free_exit(param);
	return (0);
}

int	loop(void)
{
	return (0);
}

void	draw_line(const t_vec2 p1, const t_vec2 p2, t_mlx *mlx)
{
	const t_vec2	delta = {p2.x - p1.x, p2.y - p1.y};
	const int		step = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	float			step_x;
	float			step_y;
	int				i;

	mlx_pixel_put(mlx->ptr, mlx->win_ptr, p1.x, p1.y, 0xFFFFFFFF);
	if (step == 0)
		return ;
	step_x = (float)delta.x / step;
	step_y = (float)delta.y / step;
	i = 0;
	while (++i <= step)
		mlx_pixel_put(mlx->ptr, mlx->win_ptr, roundf(p1.x + step_x * i), \
			roundf(p1.y + step_y * i), 0xFFFFFFFF);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	if (!mlx.ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.ptr, 640, 480, "fdf");
	if (!mlx.win_ptr)
		return (1);
	draw_line((t_vec2){4, 8}, (t_vec2){3, 3}, &mlx);
	draw_line((t_vec2){-10, -10}, (t_vec2){1, 1}, &mlx);
	draw_line((t_vec2){10, 10}, (t_vec2){10, 10}, &mlx);
	draw_line((t_vec2){20, 20}, (t_vec2){20, 30}, &mlx);
	draw_line((t_vec2){20, 20}, (t_vec2){30, 20}, &mlx);
	mlx_key_hook(mlx.win_ptr, &key_handler, &mlx);
	mlx_loop_hook(mlx.ptr, &loop, NULL);
	mlx_loop(mlx.ptr);
}
