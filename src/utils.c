/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:22:39 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/17 11:28:58 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

t_list	*get_file_lines(const char *const file)
{
	const int	fd = open(file, O_RDONLY);
	char		*line;
	t_list		*lines;
	t_list		*node;

	if (fd == -1)
		return (NULL);
	lines = NULL;
	line = ft_get_next_line(fd);
	while (line)
	{
		node = ft_lstnew(line);
		if (!node)
		{
			free(line);
			ft_lstclear(&lines, &free);
			break ;
		}
		ft_lstadd_back(&lines, node);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	count_str_values(const char *str, const char delim)
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
