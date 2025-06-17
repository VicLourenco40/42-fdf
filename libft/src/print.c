/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:13:31 by vde-albu          #+#    #+#             */
/*   Updated: 2025/04/25 12:15:09 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

size_t	print_char(char c)
{
	return (write(1, &c, 1));
}

size_t	print_str(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}

size_t	print_nbr(long n, bool sign, bool space)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i += print_char('-');
	}
	else if (sign)
		i += print_char('+');
	else if (space)
		i += print_char(' ');
	if (n / 10)
		i += print_nbr(n / 10, false, false);
	print_char('0' + (n % 10));
	return (i);
}

size_t	print_nbr_hex(unsigned long n, bool lower, bool prefix)
{
	size_t	i;

	i = 1;
	if (prefix && n)
	{
		if (lower)
			i += print_str("0x");
		else
			i += print_str("0X");
	}
	if (n / 16)
		i += print_nbr_hex(n / 16, lower, false);
	if ((n % 16) >= 10)
		print_char('A' + (lower * 32) + (n % 16) - 10);
	else
		print_char('0' + (n % 16));
	return (i);
}

size_t	print_ptr(void *ptr)
{
	if (!ptr)
		return (print_str("(nil)"));
	return (print_nbr_hex((unsigned long)ptr, true, true));
}
