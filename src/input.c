/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:52:41 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/13 17:45:25 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#include <X11/keysym.h>

int	handle_key_down(int keycode, t_keys *keys)
{
	if (keycode == XK_Escape)
		keys->escape = 1;
	return (0);
}

int	handle_key_up(int keycode, t_keys *keys)
{
	if (keycode == XK_Escape)
		keys->escape = 0;
	return (0);
}
