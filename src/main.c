/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/06 18:01:33 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>

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

void	print_map(t_map *map)
{
	int	x;
	int	y;

	x = -1;
	while (++x < map->size.x)
	{
		y = -1;
		while (++y < map->size.y)
			ft_printf("%d\t", map->points[x][y]);
		ft_printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;
	t_image	image;

	parse_map("./test_maps/42.fdf", &map);
	print_map(&map);
	free(map.points[0]);
	free(map.points);
	return (0);
	mlx.ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	image.ptr = mlx_new_image(mlx.ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	image.data = mlx_get_data_addr(image.ptr, &image.color_depth, \
		&image.line_size, &image.endian);
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, image.ptr, 0, 0);
	mlx_destroy_image(mlx.ptr, image.ptr);
	mlx_key_hook(mlx.win_ptr, &key_handler, &mlx);
	mlx_loop(mlx.ptr);
}
