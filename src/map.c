/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:59:48 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/18 10:38:18 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>

#include <stdlib.h>

static void	init_map(t_map *const map, t_vec2 size)
{
	if (size.x == 0 || size.y == 0)
		return ;
	map->points = ft_calloc(size.x, sizeof(int *));
	map->colors = ft_calloc(size.x, sizeof(t_color *));
	if (!map->points || !map->colors)
		return (free_map(map));
	map->points[0] = ft_calloc(size.x * size.y, sizeof(int));
	map->colors[0] = ft_calloc(size.x * size.y, sizeof(t_color));
	if (!map->points[0] || !map->colors[0])
		return (free_map(map));
	ft_memset(map->colors[0], 255, size.x * size.y * sizeof(t_color));
	map->size = size;
	while (--size.x)
	{
		map->points[size.x] = map->points[0] + (size.x * size.y);
		map->colors[size.x] = map->colors[0] + (size.x * size.y);
	}
}

void	free_map(t_map *const map)
{
	if (map->points)
	{
		free(map->points[0]);
		free(map->points);
	}
	if (map->colors)
	{
		free(map->colors[0]);
		free(map->colors);
	}
	ft_bzero(map, sizeof(t_map));
}

static void	parse_line(const char *line, int *const points,
	t_color *const colors)
{
	bool	in_delim;
	int		i;

	in_delim = true;
	i = 0;
	while (*line && *line != '\n')
	{
		if (in_delim && *line != ' ')
			points[i++] = ft_atoi(line);
		if (ft_strnstr(line, ",0x", 3) || ft_strnstr(line, ",0X", 3))
			((int *)colors)[i - 1] = ft_atoi_hex(line + 3);
		in_delim = *line == ' ';
		line++;
	}
}

void	parse_map(const char *const file, t_map *const map)
{
	t_list	*lines;
	t_list	*line;
	int		x;

	lines = get_file_lines(file);
	if (!lines)
		return ;
	init_map(map, (t_vec2){ft_lstsize(lines), \
		count_str_values(lines->content, ' ')});
	line = lines;
	x = -1;
	while (++x < map->size.x)
	{
		if (count_str_values(line->content, ' ') != map->size.y)
		{
			free_map(map);
			break ;
		}
		parse_line(line->content, map->points[x], map->colors[x]);
		line = line->next;
	}
	ft_lstclear(&lines, &free);
}

void	render_map(const t_mlx *const mlx, const t_map *const map,
	t_camera *const camera)
{
	const t_vec2	i = {ft_signf(camera->cos.y), ft_signf(camera->sin.y)};
	t_vec2			c;

	c.x = (i.x < 0) * (map->size.x - 1);
	while (c.x >= 0 && c.x < map->size.x)
	{
		c.y = (i.y < 0) * (map->size.y - 1);
		while (c.y >= 0 && c.y < map->size.y)
		{
			if (c.x == 0 && c.y == 0)
				put_image_pixel(&camera->image, camera->points[0][0],
					map->colors[0][0]);
			if (c.x)
				put_image_line(&camera->image, (t_line){\
					{camera->points[c.x][c.y], camera->points[c.x - 1][c.y]}, \
					{map->colors[c.x][c.y], map->colors[c.x - 1][c.y]}});
			if (c.y)
				put_image_line(&camera->image, (t_line){\
					{camera->points[c.x][c.y], camera->points[c.x][c.y - 1]}, \
					{map->colors[c.x][c.y], map->colors[c.x][c.y - 1]}});
			c.y += i.y;
		}
		c.x += i.x;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, camera->image.ptr, 0, 0);
}
