/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:59:48 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 18:40:04 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static t_list	*get_file_lines(const char *const file)
{
	const int	fd = open(file, O_RDONLY);
	char		*line;
	t_list		*lines;
	t_list		*node;

	if (fd == -1)
		return (NULL);
	lines = NULL;
	while (true)
	{
		line = ft_get_next_line(fd);
		if (!line)
			break ;
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			ft_lstclear(&lines, &free);
			return (NULL);
		}
		ft_lstadd_back(&lines, node);
	}
	close(fd);
	return (lines);
}

static int	count_values(const char *str, const char delim)
{
	int		count;
	bool	in_delim;

	count = 0;
	in_delim = true;
	while (*str && *str != '\n')
	{
		if (in_delim && *str != delim)
			count++;
		in_delim = *str == delim;
		str++;
	}
	return (count);
}

static void	str_to_ints(const char *str, const char delim, int *ints)
{
	bool	in_delim;

	in_delim = true;
	while (*str && *str != '\n')
	{
		if (in_delim && *str != delim)
			*ints++ = ft_atoi(str);
		in_delim = *str == delim;
		str++;
	}
}

static void	init_map(t_map *const map, t_vec2 size)
{
	map->size = size;
	map->points = ft_calloc(size.x, sizeof(int *));
	if (!map->points)
	{
		ft_bzero(map, sizeof(t_map));
		return ;
	}
	map->points[0] = ft_calloc(size.x * size.y, sizeof(int));
	if (!map->points[0])
	{
		free(map->points);
		ft_bzero(map, sizeof(t_map));
		return ;
	}
	while (--size.x)
		map->points[size.x] = map->points[0] + (size.x * size.y);
}

void	parse_map(const char *const file, t_map *const map)
{
	t_list	*lines;
	t_list	*line;
	int		x;

	ft_bzero(map, sizeof(t_map));
	lines = get_file_lines(file);
	if (!lines)
		return ;
	init_map(map, \
		(t_vec2){ft_lstsize(lines), count_values(lines->content, ' ')});
	x = -1;
	line = lines;
	while (++x < map->size.x)
	{
		if (count_values(line->content, ' ') != map->size.y)
		{
			free(map->points[0]);
			free(map->points);
			ft_bzero(map, sizeof(t_map));
			break ;
		}
		str_to_ints(line->content, ' ', map->points[x]);
		line = line->next;
	}
	ft_lstclear(&lines, &free);
}
