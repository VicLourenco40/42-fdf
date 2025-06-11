/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:24:01 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 12:10:01 by vde-albu         ###   ########.fr       */
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
	return (0);
}

static bool	init(const char *const file, const t_all *const all)
{
	parse_map(file, all->map);
	if (!all->map->points)
		return (false);
	init_mlx(all->mlx);
	if (!all->mlx->ptr)
		return (false);
	init_camera(all->camera, all->mlx->ptr, all->map->size);
	if (!all->camera->points)
		return (false);
	return (true);
}

static int	loop(const t_all *const all)
{
	project_map(all->map, all->camera, all->mlx);
	return (0);
}

void	free_all(const t_all *const all)
{
	free_map(all->map);
	free_camera(all->camera, all->mlx->ptr);
	free_mlx(all->mlx);
}

int	main(int argc, char **argv)
{
	static t_map	map;
	static t_mlx	mlx;
	static t_camera	camera;
	const t_all		all = {&mlx, &map, &camera};

	if (argc < 2)
	{
		ft_putstr_fd("usage: fdf <file>\n", 1);
		return (1);
	}
	if (!init(argv[1], &all))
	{
		ft_putstr_fd("fdf: initialization error\n", 2);
		free_all(&all);
		return (1);
	}
	mlx_key_hook(mlx.win_ptr, &handle_key, (void *) &all);
	mlx_loop_hook(mlx.ptr, &loop, (void *) &all);
	mlx_loop(mlx.ptr);
	free_all(&all);
}
