/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/23 16:34:15 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/23 13:07:23 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3d *vec3d_coord(t_vec3d *coord, float x, float y, float z)
{
	coord = malloc(sizeof(t_vec3d));
    coord->x = x;
    coord->y = y;
    coord->z = z;
    return (coord);
}

void	draw_point(t_screen *screen_data, int x, int y, int z)
{
	t_vec3d *coord;

	coord = NULL;
	coord = define_vec3d_coord(coord, x, y, z);
	t_vec3d *p_point = project_point(screen_data->mat_proj, coord);
	my_mlx_pixel_put(&screen_data->img_data, p_point->x, p_point->y, 0x00ff0000);
	free(coord);
}

void	draw_line(t_vec3d *coord1, t_vec3d *coord2, t_screen *screen_data, int color)
{
	coord1 = project_point(screen_data->mat_proj, coord1);
	coord2 = project_point(screen_data->mat_proj, coord2);
	t_coord r_c1;
	t_coord r_c2;

	define_coord(&r_c1, coord1->x, coord1->y);
	define_coord(&r_c2, coord2->x, coord2->y);
	print_line(r_c1, r_c2,
		&screen_data->img_data, color);
	free(coord1);
	free(coord2);
}

int	render_next_frame(t_screen *screen_data)
{
	//point1
	t_vec3d coord1;
	t_vec3d coord2;

	//reperes
	draw_line(vec3d_coord(&coord1, 30, 30, 100), vec3d_coord(&coord2, 1, 0, 0), screen_data, 0x000000FF);
	// draw_line(vec3d_coord(&coord1, 0,0,0), vec3d_coord(&coord2, 0, 1, 0), screen_data, 0x00ff0000);
	// draw_line(vec3d_coord(&coord1, 0,0,0), vec3d_coord(&coord2, 0, 0, 1), screen_data, 0x0000FF00);
	//
	// draw_line(vec3d_coord(&coord1, 0,0,0), vec3d_coord(&coord2, 1, 0, 0), screen_data, 0x00ff00ff);
	// draw_line(vec3d_coord(&coord1, 1,0,0), vec3d_coord(&coord2, 1, 1, 0), screen_data, 0x00ff00ff);
	// draw_line(vec3d_coord(&coord1, 1,1,0), vec3d_coord(&coord2, 0, 1, 0), screen_data, 0x00ff00ff);
	// draw_line(vec3d_coord(&coord1, 0,1,0), vec3d_coord(&coord2, 0, 0, 0), screen_data, 0x00ff00ff);
	// // //color 2
	// draw_line(vec3d_coord(&coord1, 0,0,1), vec3d_coord(&coord2, 1, 0, 1), screen_data, 0x000000ff);
	// draw_line(vec3d_coord(&coord1, 1,0,1), vec3d_coord(&coord2, 1, 1, 1), screen_data, 0x000000ff);
	// draw_line(vec3d_coord(&coord1, 1,1,1), vec3d_coord(&coord2, 0, 1, 1), screen_data, 0x000000ff);
	// draw_line(vec3d_coord(&coord1, 0,1,1), vec3d_coord(&coord2, 0, 0, 1), screen_data, 0x000000ff);
	// // //color 2
	// draw_line(vec3d_coord(&coord1, 0,0,1), vec3d_coord(&coord2, 0, 0, 0), screen_data, 0x00FF0000);
	// draw_line(vec3d_coord(&coord1, 1,0,1), vec3d_coord(&coord2, 1, 0, 0), screen_data, 0x00FF0000);
	// draw_line(vec3d_coord(&coord1, 1,1,1), vec3d_coord(&coord2, 1, 1, 0), screen_data, 0x00FF0000);
	// draw_line(vec3d_coord(&coord1, 0,1,1), vec3d_coord(&coord2, 0, 1, 0), screen_data, 0x00FF0000);
	// printf("%f, %f\n", p_point->x, p_point->y);
	// print_line(define_coord(&coord1, 0, 0), define_coord(&coord2, 500, 50),
	// 	&screen_data->img_data, 0x00ff00ff);
	mlx_put_image_to_window(screen_data->mlx, screen_data->win,
		screen_data->img_data.img, 0, 0);
	return (0);
}
