/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/04 15:57:38 by vde-albu         ###   ########.fr       */
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
	if (keycode == KEY_ESCAPE)
		free_exit(param);
	return (0);
}

int	loop(void)
{
	return (0);
}

void	put_pixel(t_image *const image, const t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || \
		pos.x >= WINDOW_WIDTH || pos.y >= WINDOW_HEIGHT)
		return ;
	((int *)(image->data + pos.y * image->line_size))[pos.x] = 0xFFFFFFFF;
}

void	put_line(t_image *const image, const t_vec2 p1, const t_vec2 p2)
{
	const t_vec2	delta = {p2.x - p1.x, p2.y - p1.y};
	const int		step = ft_max(ft_abs(delta.x), ft_abs(delta.y));
	float			step_x;
	float			step_y;
	int				i;

	put_pixel(image, p1);
	if (step == 0)
		return ;
	step_x = (float)delta.x / step;
	step_y = (float)delta.y / step;
	i = 0;
	while (++i <= step)
		put_pixel(image, \
			(t_vec2){roundf(p1.x + step_x * i), roundf(p1.y + step_y * i)});
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_image	image;

	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	image.ptr = mlx_new_image(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	image.data = mlx_get_data_addr(image.ptr, &image.color_depth, \
		&image.line_size, &image.endian);
	put_line(&image, (t_vec2){-1000, -1000}, (t_vec2){10000, 10000});
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, image.ptr, 0, 0);
	mlx_destroy_image(mlx.ptr, image.ptr);
	mlx_key_hook(mlx.win_ptr, &key_handler, &mlx);
	mlx_loop_hook(mlx.ptr, &loop, NULL);
	mlx_loop(mlx.ptr);
}
