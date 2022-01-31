/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:54:32 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/31 17:47:44 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	<stdio.h>
# include	<mlx.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<stdarg.h>
# include	"libft/libft.h"
# include   <math.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

//touch
// # define ESCAPE 65307
# define ESCAPE 53
# define A_TOUCH 0
# define D_TOUCH 2
# define W_TOUCH 1
# define S_TOUCH 13

typedef struct s_vec3d
{
    float x;
    float y;
    float z;
}   t_vec3d;

typedef struct s_mat4x4
{
    float   m[4][4];
}   t_mat4x4;

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
	int			*map_data;
	t_mat4x4	*mat_proj;
	int			fov;
	t_mat4x4	*mat_rot_x;
	t_mat4x4	*mat_rot_z;
	float		rotation_z;
	float		rotation_x;
	int			key_press;
	t_list		*vectors;
}	t_screen;

/* OTHERS */
void    	multiply_matrix_vector(t_vec3d *in, t_vec3d *out, t_mat4x4 *mat);
void  	  clean_4(t_mat4x4 *matrix);
t_mat4x4    *matrix_rotation_x(float fElapsedTime);
t_mat4x4    *matrix_rotation_z(float fElapsedTime);
int			verify_pressed(t_screen *screen_data);
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
void	print_line(t_coord coord0, t_coord coord1,
				t_img_data *img_data, int color);
void	clean_screen(t_screen *screen_data);

/* PIXEL INTERFACE */
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

/* UTILS */
t_coord		define_coord(t_coord *coord, int x, int y);
t_vec3d 	*vec3d_coord(t_vec3d *coord, float x, float y, float z);
int			tern(int condition, int a, int b);
int			ft_abs(int a);
int			ft_atoi(const char *nptr);

/* PROJECTION */
t_mat4x4	*projection(t_mat4x4 *mat_proj, float fFov);
t_vec3d		*project_point(t_mat4x4 *mat_proj, t_vec3d *coord);
t_vec3d 	*define_vec3d_coord(t_vec3d *coord, float x, float y, float z);

#endif