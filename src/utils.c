/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:22:39 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/12 15:07:54 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
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

int	ft_atoi_hex(const char *nptr)
{
	int	num;

	while (ft_isspace(*nptr))
		nptr++;
	num = 0;
	while (*nptr)
	{
		if (ft_isdigit(*nptr))
			num = num * 16 + *nptr++ - '0';
		else if (*nptr >= 'a' && *nptr <= 'f')
			num = num * 16 + 10 + *nptr++ - 'a';
		else if (*nptr >= 'A' && *nptr <= 'F')
			num = num * 16 + 10 + *nptr++ - 'A';
		else
			break ;
	}
	return (num);
}

void	str_to_ints(const char *str, int *ints, t_color *colors)
{
	bool	in_delim;

	in_delim = true;
	while (*str && *str != '\n')
	{
		if (in_delim && *str != ' ')
			*ints++ = ft_atoi(str);
		if (ft_strnstr(str, ",0x", 3) || ft_strnstr(str, ",0X", 3))
			*(int *)colors++ = ft_atoi_hex(str + 3);
		in_delim = *str == ' ';
		str++;
	}
}
