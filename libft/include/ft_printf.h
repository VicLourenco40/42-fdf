/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:48:57 by vde-albu          #+#    #+#             */
/*   Updated: 2025/04/25 12:05:31 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdbool.h>
# include <stddef.h>

typedef struct s_flags
{
	bool	hex;
	bool	space;
	bool	sign;
}	t_flags;

int		ft_printf(const char *format, ...);
size_t	print_char(char c);
size_t	print_str(char *s);
size_t	print_nbr(long n, bool sign, bool space);
size_t	print_nbr_hex(unsigned long n, bool lower, bool prefix);
size_t	print_ptr(void *ptr);

#endif
