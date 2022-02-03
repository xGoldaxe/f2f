/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:54:32 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:50:36 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	<stdio.h>
# include	"minilibx-linux/mlx.h"
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<stdarg.h>
# include	"libft/libft.h"
# include	<math.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

//touch
# define ESCAPE 65307
// # define ESCAPE 53
# define A_TOUCH 97
# define D_TOUCH 100
# define W_TOUCH 115
# define S_TOUCH 119
# define MINUS_TOUCH 65453
# define PLUS_TOUCH 65451

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_mat4x4
{
	float	m[4][4];
}	t_mat4x4;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_size {
	int	width;
	int	height;
}	t_size;

typedef struct s_coord {
	int	x;
	int	y;
}	t_coord;

typedef struct s_screen {
	void		*mlx;
	void		*win;
	t_img_data	img_data;
	t_mat4x4	*mat_proj;
	int			fov;
	t_mat4x4	*mat_rot_x;
	t_mat4x4	*mat_rot_z;
	float		rotation_z;
	float		rotation_x;
	int			key_press;
	t_vec3d		**vectors;
	int			map_x;
	int			map_y;
	int			max_z;
	int			min_z;
	float		z_divisor;
	int			proj_type;
}	t_screen;

/* OTHERS */
void		multiply_matrix_vector(t_vec3d *in, t_vec3d *out, t_mat4x4 *mat);
void		clean_4(t_mat4x4 *matrix);
t_mat4x4	*matrix_rotation_x(float fElapsedTime);
t_mat4x4	*matrix_rotation_z(float fElapsedTime);
int			verify_pressed(t_screen *screen_data);
t_vec3d		*rotate(t_mat4x4 *mat_rot, t_vec3d *vec3d);
t_vec3d		*vec3d_coord(t_vec3d *coord, float x, float y, float z);
t_vec3d		*vec3d_coord_upd(t_vec3d *coord, float x, float y, float z);
float		*get_ratio(t_screen *s, float *ratio);

/* EXECUTION */
int			render_next_frame(t_screen *screen_data);
int			clean_exit(t_screen *screen_data);

/* PARSING */
void		*parse_map(char *filename_map, t_screen *screen);

/* EVENTS */
int			on_press(int keycode, t_screen *screen_data);

/* COLORS */
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			create_trgb(int t, int r, int g, int b);

/* PUT SHAPES */
void		print_line(t_coord coord0, t_coord coord1,
				t_img_data *img_data, int color);
void		clean_screen(t_screen *screen_data);

/* PIXEL INTERFACE */
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

/* UTILS */
t_coord		define_coord(t_coord *coord, int x, int y);
t_vec3d		*vec3d_coord(t_vec3d *coord, float x, float y, float z);
int			tern(int condition, int a, int b);
int			ft_abs(int a);
int			ft_atoi(const char *nptr);
void		*free_split(void **entry);
char		*ft_realloc_cat(char *src, char *dst);
char		*read_file(char *filename);
char		**read_lines(char *filename_map);
float		float_tern(int condition, float a, float b);

/* PROJECTION */
t_mat4x4	*projection(float f_fov);
t_vec3d		*project_point(t_mat4x4 *mat_proj,
				t_vec3d *coord, t_screen *screen_data);
t_vec3d		*define_vec3d_coord(t_vec3d *coord, float x, float y, float z);
//*iso
t_mat4x4	*iso_projection(void);

/* EVENTS */
int			verify_pressed(t_screen *screen_data);
int			on_press(int keycode, t_screen *screen_data);
int			on_release(int keycode, t_screen *screen_data);
int			mouse_hook(int keycode, int x, int y, t_screen *screen_data);
int			default_options(t_screen *screen_data, char *entry);

#endif