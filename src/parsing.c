/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:59:48 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/06 18:02:36 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <libft.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_list	*get_file_lines(char *file)
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
	return (lines);
}

size_t	count_values(char *str, char delim)
{
	size_t	count;
	bool	in_delim;

	count = 0;
	in_delim = true;
	while (*str)
	{
		if (in_delim && *str != delim)
			count++;
		in_delim = *str == delim;
		str++;
	}
	return (count);
}

void	str_to_ints(char *str, char delim, int *ints)
{
	bool	in_delim;
	int		i;

	in_delim = true;
	i = 0;
	while (*str)
	{
		if (in_delim && *str != delim)
			ints[i++] = ft_atoi(str);
		in_delim = *str == delim;
		str++;
	}
}

void	lines_to_map(t_list *lines, t_map *map)
{
	int	x;

	x = 0;
	while (x < map->size.x)
	{
		str_to_ints(lines->content, ' ', map->points[x++]);
		lines = lines->next;
	}
}

void	parse_map(char *file, t_map *map)
{
	t_list	*lines;
	int		x;

	lines = get_file_lines(file);
	if (!lines)
		return ;
	map->size.x = ft_lstsize(lines);
	map->size.y = count_values(lines->content, ' ');
	map->points = ft_calloc(map->size.x, sizeof(int *));
	if (!map->points)
		return ;
	map->points[0] = ft_calloc(map->size.x * map->size.y, sizeof(int));
	if (!map->points[0])
	{
		free(map->points);
		ft_lstclear(&lines, &free);
		return ;
	}
	x = 0;
	while (++x < map->size.x)
		map->points[x] = map->points[x - 1] + map->size.y;
	lines_to_map(lines, map);
	ft_lstclear(&lines, &free);
}
