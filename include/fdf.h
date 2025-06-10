/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:28:33 by vde-albu          #+#    #+#             */
/*   Updated: 2025/06/10 10:54:14 by vde-albu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

# define KEY_ESCAPE 65307

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

typedef struct s_camera
{
	t_vec2	position;
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

void	parse_map(const char *const file, t_map *const map);
void	free_map(t_map *const map);
void	init_mlx(t_mlx *const mlx);
void	init_camera(t_camera *const camera, void *mlx, t_vec2 size);
void	put_image_pixel(t_image *const image, const t_vec2 pos);
void	put_image_line(t_image *const image, const t_vec2 p1, const t_vec2 p2);
void	project_map(const t_map *const map, t_camera *const camera, \
	t_mlx *const mlx);

#endif
