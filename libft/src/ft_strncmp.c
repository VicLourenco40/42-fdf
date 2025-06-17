/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:19:00 by vde-albu          #+#    #+#             */
/*   Updated: 2025/04/14 14:19:57 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	u1;
	unsigned char	u2;
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		u1 = s1[i];
		u2 = s2[i];
		if (u1 != u2)
			return (u1 - u2);
		i++;
	}
	return (0);
}
