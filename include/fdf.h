/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:28:33 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/12 11:18:08 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

# define WINDOW_WIDTH			1280
# define WINDOW_HEIGHT			720

# define KEY_ESCAPE				65307
# define KEY_MINUS				45
# define KEY_PLUS				61
# define KEY_SQ_BRACKET_LEFT	91
# define KEY_SQ_BRACKET_RIGHT	93
# define KEY_A					97
# define KEY_D					100
# define KEY_S					115
# define KEY_W					119
# define KEY_LEFT				65361
# define KEY_UP					65362
# define KEY_RIGHT				65363
# define KEY_DOWN				65364

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
	char	a;
	char	r;
	char	g;
	char	b;
}	t_color;

typedef struct s_map
{
	int		**points;
	t_color	**colors;
	t_vec2	size;
}	t_map;

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

typedef struct s_state
{
	t_mlx		mlx;
	t_map		map;
	t_camera	camera;
}	t_state;

void	parse_map(const char *const file, t_map *const map);
void	free_map(t_map *const map);
void	init_mlx(t_mlx *const mlx);
void	free_mlx(t_mlx *const mlx);
void	init_camera(t_camera *const camera, void *mlx, t_vec2 size);
void	free_camera(t_camera *const camera, void *mlx);
void	put_image_pixel(t_image *const image, const t_vec2 point,
			const t_color color);
void	put_image_line(t_image *const image, const t_vec2 p1, const t_color c1,
			const t_vec2 p2, const t_color c2);
void	project_map(const t_map *const map, t_camera *const camera,
			t_mlx *const mlx);
t_list	*get_file_lines(const char *const file);
int		count_str_values(const char *str, const char delim);
void	str_to_ints(const char *str, int *ints, t_color *colors);

#endif
