/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:59:48 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/12 16:19:38 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <stdlib.h>

static void	init_map(t_map *const map, t_vec2 size)
{
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

static void	parse_line(const char *line, int *points, t_color *colors)
{
	bool	in_delim;

	in_delim = true;
	while (*line && *line != '\n')
	{
		if (in_delim && *line != ' ')
			*points++ = ft_atoi(line);
		if (ft_strnstr(line, ",0x", 3) || ft_strnstr(line, ",0X", 3))
			*(int *)colors++ = ft_atoi_hex(line + 3);
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
