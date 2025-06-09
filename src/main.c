/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 13:02:01 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>

static int	handle_key(const int keycode, const t_mlx *const mlx)
{
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(mlx->ptr);
	return (0);
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
	mlx_key_hook(mlx.win_ptr, &handle_key, &mlx);
	mlx_loop(mlx.ptr);
	mlx_destroy_image(mlx.ptr, mlx.image.ptr);
	mlx_destroy_window(mlx.ptr, mlx.win_ptr);
	mlx_destroy_display(mlx.ptr);
	free(mlx.ptr);
	free(map.points[0]);
	free(map.points);
}
