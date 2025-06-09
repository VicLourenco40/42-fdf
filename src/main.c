/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 12:46:29 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>

static int	key_handler(const int keycode, const t_mlx *const mlx)
{
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(mlx->ptr);
	return (0);
}

static void	init_mlx(t_mlx *const mlx)
{
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return ;
	mlx->win_ptr = mlx_new_window(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		mlx->ptr = NULL;
		return ;
	}
	mlx->image.ptr = mlx_new_image(mlx->ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->image.ptr)
	{
		mlx_destroy_window(mlx->ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->ptr);
		free(mlx->ptr);
		ft_bzero(mlx, sizeof(t_mlx));
		return ;
	}
	mlx->image.data = mlx_get_data_addr(mlx->image.ptr, \
		&mlx->image.color_depth, &mlx->image.line_size, &mlx->image.endian);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;

	if (argc < 2)
	{
		ft_putstr_fd("usage: fdf <file>\n", 1);
		return (1);
	}
	parse_map(argv[1], &map);
	if (!map.points)
	{
		ft_putstr_fd("fdf: parsing error\n", 2);
		return (1);
	}
	init_mlx(&mlx);
	if (!mlx.ptr)
	{
		ft_putstr_fd("fdf: mlx error\n", 2);
		return (1);
	}
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.image.ptr, 0, 0);
	mlx_key_hook(mlx.win_ptr, &key_handler, &mlx);
	mlx_loop(mlx.ptr);
	mlx_destroy_image(mlx.ptr, mlx.image.ptr);
	mlx_destroy_window(mlx.ptr, mlx.win_ptr);
	mlx_destroy_display(mlx.ptr);
	free(mlx.ptr);
	free(map.points[0]);
	free(map.points);
}
