/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/30 16:58:32 by pleveque         ###   ########.fr       */
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
	t_vec3d *tmp_coord1;
	t_vec3d *tmp_coord2;

	tmp_coord1 = project_point(screen_data->mat_proj, coord1);
	tmp_coord2 = project_point(screen_data->mat_proj, coord2);
	t_coord r_c1;
	t_coord r_c2;

	define_coord(&r_c1, tmp_coord1->x, tmp_coord1->y);
	define_coord(&r_c2, tmp_coord2->x, tmp_coord2->y);
	print_line(r_c1, r_c2,
		&screen_data->img_data, color);
	free(tmp_coord1);
	free(tmp_coord2);
}

t_vec3d *vec3d_coord_upd(t_vec3d *coord, float x, float y, float z)
{
    coord->x = x;
    coord->y = y;
    coord->z = z;
    return (coord);
}

t_vec3d *vec3d_coord(t_vec3d *coord, float x, float y, float z)
{
	coord = malloc(sizeof(t_vec3d));
    coord->x = x;
    coord->y = y;
    coord->z = z;
    return (coord);
}

t_mat4x4    *matrix_rotation_x(float fElapsedTime)
{
	t_mat4x4    *matRotX;
	float       fTheta = 1.0 * fElapsedTime;

	matRotX = malloc(sizeof(t_mat4x4));
    clean_4(matRotX);
	// Rotation Z
	matRotX->m[0][0] = 1;
	matRotX->m[1][1] = cos(fTheta);
	matRotX->m[1][2] = sin(fTheta);
	matRotX->m[2][1] = -sin(fTheta);
	matRotX->m[2][2] = cos(fTheta);
	matRotX->m[3][3] = 1;
    return (matRotX);
}

t_mat4x4    *matrix_rotation_z(float fElapsedTime)
{
	t_mat4x4    *matRotZ;
	float       fTheta = 1.0 * fElapsedTime;

	matRotZ = malloc(sizeof(t_mat4x4));
    clean_4(matRotZ);
	// Rotation Z
	matRotZ->m[0][0] = cos(fTheta);
	matRotZ->m[0][1] = sin(fTheta);
	matRotZ->m[1][0] = -sin(fTheta);
	matRotZ->m[1][1] = cos(fTheta);
	matRotZ->m[2][2] = 1;
	matRotZ->m[3][3] = 1;
    return (matRotZ);
}

t_vec3d		*rotate_x(t_mat4x4 *mat_rot_x, t_vec3d *vec3d)
{
	t_vec3d *coords_rot_x = 0;
	
	coords_rot_x = vec3d_coord(coords_rot_x, 0, 0, 0);
	multiply_matrix_vector(vec3d, coords_rot_x, mat_rot_x);
	free(vec3d);
	vec3d = coords_rot_x;
	vec3d->z += 3;
	return (vec3d);
}

t_vec3d		*rotate_z(t_mat4x4 *mat_rot_z, t_vec3d *vec3d)
{
	t_vec3d *coords_rot_z = 0;
	
	coords_rot_z = vec3d_coord(coords_rot_z, 0, 0, 0);
	multiply_matrix_vector(vec3d, coords_rot_z, mat_rot_z);
	free(vec3d);
	vec3d = coords_rot_z;
	return (vec3d);
}

int	render_next_frame(t_screen *screen_data)
{
	//point1
	t_vec3d			*coords[4];
	static float	first_i = 0;
	t_mat4x4		*mat_rot_x;
	t_mat4x4		*mat_rot_z;

	clean_screen(screen_data);
	// if (first_i == 0)
	//{
	coords[0] = 0;
	coords[1] = 0;
	coords[2] = 0;
	coords[3] = 0;
	coords[0] = vec3d_coord(coords[0], -0.5, -0.5, 0.5);
	coords[1] = vec3d_coord(coords[1], 0.5, -0.5, 0.5);
	coords[2] = vec3d_coord(coords[2], 0.5, 0.5, 0.5);
	coords[3] = vec3d_coord(coords[3], -0.5, 0.5, 0.5);
	//}
 	first_i += 0.01;
	mat_rot_x = matrix_rotation_x(first_i);
	mat_rot_z = matrix_rotation_z(first_i / 2);

	coords[0] = rotate_z(mat_rot_z, coords[0]);
	coords[1] = rotate_z(mat_rot_z, coords[1]);
	coords[2] = rotate_z(mat_rot_z, coords[2]);
	coords[3] = rotate_z(mat_rot_z, coords[3]);

	coords[0] = rotate_x(mat_rot_x, coords[0]);
	coords[1] = rotate_x(mat_rot_x, coords[1]);
	coords[2] = rotate_x(mat_rot_x, coords[2]);
	coords[3] = rotate_x(mat_rot_x, coords[3]);

	draw_line(coords[0], coords[1], screen_data, 0x00ff00ff);
	draw_line(coords[1], coords[2], screen_data, 0x00ff00ff);
	draw_line(coords[2], coords[3], screen_data, 0x00ff00ff);
	draw_line(coords[3], coords[0], screen_data, 0x00ff00ff);
// //back ================================================
	coords[0] = vec3d_coord_upd(coords[0], -0.5, -0.5, -0.5);
	coords[1] = vec3d_coord_upd(coords[1], 0.5, -0.5, -0.5);
	coords[2] = vec3d_coord_upd(coords[2], 0.5, 0.5, -0.5);
	coords[3] = vec3d_coord_upd(coords[3], -0.5, 0.5, -0.5);

	coords[0] = rotate_z(mat_rot_z, coords[0]);
	coords[1] = rotate_z(mat_rot_z, coords[1]);
	coords[2] = rotate_z(mat_rot_z, coords[2]);
	coords[3] = rotate_z(mat_rot_z, coords[3]);

	coords[0] = rotate_x(mat_rot_x, coords[0]);
	coords[1] = rotate_x(mat_rot_x, coords[1]);
	coords[2] = rotate_x(mat_rot_x, coords[2]);
	coords[3] = rotate_x(mat_rot_x, coords[3]);

	draw_line(coords[0], coords[1], screen_data, 0x00ff00ff);
	draw_line(coords[1], coords[2], screen_data, 0x00ff00ff);
	draw_line(coords[2], coords[3], screen_data, 0x00ff00ff);
	draw_line(coords[3], coords[0], screen_data, 0x00ff00ff);
// // left ==========================================
	coords[0] = vec3d_coord_upd(coords[0], -0.5, -0.5, 0.5);
	coords[1] = vec3d_coord_upd(coords[1], -0.5, -0.5, -0.5);
	coords[2] = vec3d_coord_upd(coords[2], -0.5, 0.5, 0.5);
	coords[3] = vec3d_coord_upd(coords[3], -0.5, 0.5, -0.5);

	coords[0] = rotate_z(mat_rot_z, coords[0]);
	coords[1] = rotate_z(mat_rot_z, coords[1]);
	coords[2] = rotate_z(mat_rot_z, coords[2]);
	coords[3] = rotate_z(mat_rot_z, coords[3]);

	coords[0] = rotate_x(mat_rot_x, coords[0]);
	coords[1] = rotate_x(mat_rot_x, coords[1]);
	coords[2] = rotate_x(mat_rot_x, coords[2]);
	coords[3] = rotate_x(mat_rot_x, coords[3]);
	
	draw_line(coords[0], coords[1], screen_data, 0x00ff00ff);
	draw_line(coords[2], coords[3], screen_data, 0x00ff00ff);
// // right ==========================================
	coords[0] = vec3d_coord_upd(coords[0], 0.5, -0.5, 0.5);
	coords[1] = vec3d_coord_upd(coords[1], 0.5, -0.5, -0.5);
	coords[2] = vec3d_coord_upd(coords[2], 0.5, 0.5, 0.5);
	coords[3] = vec3d_coord_upd(coords[3], 0.5, 0.5, -0.5);

	coords[0] = rotate_z(mat_rot_z, coords[0]);
	coords[1] = rotate_z(mat_rot_z, coords[1]);
	coords[2] = rotate_z(mat_rot_z, coords[2]);
	coords[3] = rotate_z(mat_rot_z, coords[3]);
	
	coords[0] = rotate_x(mat_rot_x, coords[0]);
	coords[1] = rotate_x(mat_rot_x, coords[1]);
	coords[2] = rotate_x(mat_rot_x, coords[2]);
	coords[3] = rotate_x(mat_rot_x, coords[3]);

	draw_line(coords[0], coords[1], screen_data, 0x00ff00ff);
	draw_line(coords[2], coords[3], screen_data, 0x00ff00ff);
//=============

	free(coords[0]);
	free(coords[1]);
	free(coords[2]);
	free(coords[3]);
	free(mat_rot_x);
	free(mat_rot_z);
	mlx_put_image_to_window(screen_data->mlx, screen_data->win,
		screen_data->img_data.img, 0, 0);
	return (0);
}
