/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:28:33 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/16 10:36:23 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}	t_color;

typedef struct s_map
{
	int		**points;
	t_color	**colors;
	t_vec2	size;
}	t_map;

typedef struct s_line
{
	t_vec2	points[2];
	t_color	colors[2];
}	t_line;

typedef struct s_image
{
	void	*ptr;
	t_color	*data;
	int		line_size;
	int		color_depth;
	int		endian;
}	t_image;

typedef struct s_camera
{
	t_vec2f	position;
	t_vec2f	rotation;
	t_vec2f	sin;
	t_vec2f	cos;
	float	zoom;
	float	height_scale;
	t_vec2	**points;
	t_image	image;
}	t_camera;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_keys
{
	char	escape;
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
	char	up;
	char	down;
	char	plus;
	char	minus;
}	t_keys;

typedef struct s_state
{
	t_mlx		mlx;
	t_map		map;
	t_camera	camera;
	t_keys		keys;
}	t_state;

void	parse_map(const char *const file, t_map *const map);
void	free_map(t_map *const map);
void	init_mlx(t_mlx *const mlx);
void	free_mlx(t_mlx *const mlx);
void	init_camera(t_camera *const camera, void *mlx, t_vec2 size);
void	free_camera(t_camera *const camera, void *mlx);
void	put_image_pixel(t_image *const image, const t_vec2 point,
			const t_color color);
void	put_image_line(t_image *const image, const t_line line);
void	draw_map(const t_map *const map, t_camera *const camera,
			t_mlx *const mlx);
int		handle_key_down(int keycode, t_keys *keys);
int		handle_key_up(int keycode, t_keys *keys);
void	handle_input(t_keys *const keys, t_camera *const camera,
			void *const mlx);
t_list	*get_file_lines(const char *const file);
int		count_str_values(const char *str, const char delim);

#endif
