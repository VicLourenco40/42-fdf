/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:59:48 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/11 12:27:32 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <stdlib.h>

static void	init_map(t_map *const map, t_vec2 size)
{
	map->points = ft_calloc(size.x, sizeof(int *));
	if (!map->points)
		return ;
	map->points[0] = ft_calloc(size.x * size.y, sizeof(int));
	if (!map->points[0])
		return (free_map(map));
	map->size = size;
	while (--size.x)
		map->points[size.x] = map->points[0] + (size.x * size.y);
}

void	free_map(t_map *const map)
{
	if (map->points)
	{
		free(map->points[0]);
		free(map->points);
	}
	ft_bzero(map, sizeof(t_map));
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
	x = 0;
	while (x < map->size.x)
	{
		if (count_str_values(line->content, ' ') != map->size.y)
		{
			free_map(map);
			break ;
		}
		str_to_ints(line->content, ' ', map->points[x++]);
		line = line->next;
	}
	ft_lstclear(&lines, &free);
}
