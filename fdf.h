/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:54:32 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/21 17:42:15 by pleveque         ###   ########.fr       */
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

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 1080

//touch
# define ESCAPE 65307

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
}	t_screen;

/* EXECUTION */
int			render_next_frame(t_screen *screen_data);
int			clean_exit(t_screen *screen_data);

/* PARSING */
int			*parse_map(char *filename_map);

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

/* PIXEL INTERFACE */
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

/* UTILS */
t_coord		define_coord(t_coord *coord, int x, int y);
int			tern(int condition, int a, int b);
int			ft_abs(int a);
int			ft_atoi(const char *nptr);

#endif