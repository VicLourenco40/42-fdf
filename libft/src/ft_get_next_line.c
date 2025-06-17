/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:04:35 by vde-albu          #+#    #+#             */
/*   Updated: 2025/04/25 12:02:25 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

static size_t	update_buffer(char *buffer, int fd, char **line)
{
	size_t	i;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	i = bytes_read;
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	return (bytes_read);
}

static void	shift_buffer(char *buffer, size_t len)
{
	size_t	i;

	if (len < BUFFER_SIZE)
		ft_memcpy(buffer, buffer + len, BUFFER_SIZE - len);
	i = BUFFER_SIZE - len;
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
}

static char	*append_to_line(char *old_line, char *buffer, size_t len)
{
	size_t	old_len;
	char	*line;

	old_len = 0;
	if (old_line)
		while (old_line[old_len])
			old_len++;
	line = malloc(sizeof(char) * (old_len + len + 1));
	if (!line)
	{
		free(old_line);
		return (NULL);
	}
	if (old_line)
		ft_memcpy(line, old_line, old_len);
	ft_memcpy(line + old_len, buffer, len);
	line[old_len + len] = '\0';
	free(old_line);
	return (line);
}

char	*ft_get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE];
	char		*newline;
	char		*line;
	size_t		len;

	line = NULL;
	newline = NULL;
	while (!newline)
	{
		if (!buffer[fd][0] && !update_buffer(buffer[fd], fd, &line))
			break ;
		newline = ft_memchr(buffer[fd], '\n', BUFFER_SIZE);
		if (newline)
			len = newline - buffer[fd] + 1;
		else if (ft_memchr(buffer[fd], '\0', BUFFER_SIZE))
			len = (char *)ft_memchr(buffer[fd], '\0', BUFFER_SIZE) - buffer[fd];
		else
			len = BUFFER_SIZE;
		line = append_to_line(line, buffer[fd], len);
		if (!line)
			return (NULL);
		shift_buffer(buffer[fd], len);
	}
	return (line);
}
