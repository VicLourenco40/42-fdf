/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:28:33 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/09 13:00:25 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480

# define KEY_ESCAPE 65307

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_map
{
	int		**points;
	t_vec2	size;
}	t_map;

typedef struct s_image
{
	void	*ptr;
	char	*data;
	int		line_size;
	int		color_depth;
	int		endian;
}	t_image;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
	t_image	image;
}	t_mlx;

void	parse_map(const char *const file, t_map *const map);
void	init_mlx(t_mlx *const mlx);

#endif
