/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 11:34:34 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>
#include <mlx.h>

#include <stdlib.h>
#include <math.h>

int	handle_key(const int keycode, const t_all *const all)
{
	const float	mag = 2.0f;

	//ft_printf("%d\n", keycode);
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(all->mlx->ptr);
	else if (keycode == KEY_W)
	{
		all->camera->position.x += mag * cosf(all->camera->rotation.y);
		all->camera->position.y += mag * sinf(all->camera->rotation.y);
	}
	else if (keycode == KEY_S)
	{
		all->camera->position.x -= mag * cosf(all->camera->rotation.y);
		all->camera->position.y -= mag * sinf(all->camera->rotation.y);
	}
	else if (keycode == KEY_A)
	{
		all->camera->position.x += mag * -sinf(all->camera->rotation.y);
		all->camera->position.y += mag * cosf(all->camera->rotation.y);
	}
	else if (keycode == KEY_D)
	{
		all->camera->position.x -= mag * -sinf(all->camera->rotation.y);
		all->camera->position.y -= mag * cosf(all->camera->rotation.y);
	}
	else if (keycode == KEY_UP)
		all->camera->rotation.x -= asinf(tanf(M_PI / 6)) / 4;
	else if (keycode == KEY_DOWN)
		all->camera->rotation.x += asinf(tanf(M_PI / 6)) / 4;
	else if (keycode == KEY_LEFT)
		all->camera->rotation.y -= M_PI_4 / 4;
	else if (keycode == KEY_RIGHT)
		all->camera->rotation.y += M_PI_4 / 4;
	else if (keycode == KEY_PLUS)
		all->camera->zoom = \
			ft_clampf(all->camera->zoom + 4.0f, 4.0f, 80.0f);
	else if (keycode == KEY_MINUS)
		all->camera->zoom = \
			ft_clampf(all->camera->zoom - 4.0f, 4.0f, 80.0f);
	else if (keycode == KEY_SQ_BRACKET_LEFT)
		all->camera->height_scale = \
			ft_clampf(all->camera->height_scale - 0.1f, 0.0f, 10.0f);
	else if (keycode == KEY_SQ_BRACKET_RIGHT)
		all->camera->height_scale = \
			ft_clampf(all->camera->height_scale + 0.1f, 0.0f, 10.0f);
	project_map(all->map, all->camera, all->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_mlx		mlx;
	t_camera	camera;
	const t_all	all = {&mlx, &map, &camera};

	if (argc < 2)
	{
		ft_putstr_fd("usage: fdf <file>\n", 1);
		return (1);
	}
	parse_map(argv[1], &map);
	if (!map.points)
		return (1);
	init_mlx(&mlx);
	if (!mlx.ptr)
		return (1);
	init_camera(&camera, mlx.ptr, map.size);
	if (!camera.points)
		return (1);
	project_map(&map, &camera, &mlx);
	mlx_key_hook(mlx.win_ptr, &handle_key, (void *) &all);
	mlx_loop(mlx.ptr);
	free_map(&map);
	free_camera(&camera, mlx.ptr);
	free_mlx(&mlx);
}
