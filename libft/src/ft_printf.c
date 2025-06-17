/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:14:23 by vde-albu          #+#    #+#             */
/*   Updated: 2025/04/25 12:35:22 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <libft.h>

static void	get_flags(const char **format, t_flags *flags)
{
	ft_bzero(flags, sizeof(t_flags));
	while (ft_strchr("# +", **format))
	{
		if (**format == '#')
			flags->hex = true;
		else if (**format == ' ')
			flags->space = true;
		else if (**format == '+')
			flags->sign = true;
		(*format)++;
	}
}

static size_t	print_conversion(const char **format, va_list *args)
{
	t_flags	flags;

	get_flags(format, &flags);
	if (**format == 'c')
		return (print_char(va_arg(*args, int)));
	else if (**format == 's')
		return (print_str(va_arg(*args, char *)));
	else if (**format == 'p')
		return (print_ptr(va_arg(*args, void *)));
	else if (**format == 'd' || **format == 'i')
		return (print_nbr(va_arg(*args, int), flags.sign, flags.space));
	else if (**format == 'u')
		return (print_nbr(va_arg(*args, unsigned int), false, false));
	else if (**format == 'x' || **format == 'X')
		return (print_nbr_hex(va_arg(*args, unsigned int), **format == 'x',
				flags.hex));
	else if (**format == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	printed;

	va_start(args, format);
	printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed += print_conversion(&format, &args);
		}
		else
			printed += print_char(*format);
		format++;
	}
	va_end(args);
	return (printed);
}
