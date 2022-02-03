/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:45:48 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3d	*vec3d_coord_upd(t_vec3d *coord, float x, float y, float z)
{
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

t_vec3d	*vec3d_coord(t_vec3d *coord, float x, float y, float z)
{
	coord = malloc(sizeof(t_vec3d));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

t_mat4x4	*matrix_rotation_x(float f_elapsed_time)
{
	t_mat4x4	*mat_rot_x;
	float		f_theta;

	f_theta = 1.0 * f_elapsed_time;
	mat_rot_x = malloc(sizeof(t_mat4x4));
	if (!mat_rot_x)
		return (NULL);
	clean_4(mat_rot_x);
	mat_rot_x->m[0][0] = 1;
	mat_rot_x->m[1][1] = cos(f_theta);
	mat_rot_x->m[1][2] = sin(f_theta);
	mat_rot_x->m[2][1] = -sin(f_theta);
	mat_rot_x->m[2][2] = cos(f_theta);
	mat_rot_x->m[3][3] = 1;
	return (mat_rot_x);
}

t_mat4x4	*matrix_rotation_z(float f_elapsed_time)
{
	t_mat4x4	*mat_rot_z;
	float		f_theta;

	f_theta = 1.0 * f_elapsed_time;
	mat_rot_z = malloc(sizeof(t_mat4x4));
	if (!mat_rot_z)
		return (NULL);
	clean_4(mat_rot_z);
	mat_rot_z->m[0][0] = cos(f_theta);
	mat_rot_z->m[0][1] = sin(f_theta);
	mat_rot_z->m[1][0] = -sin(f_theta);
	mat_rot_z->m[1][1] = cos(f_theta);
	mat_rot_z->m[2][2] = 1;
	mat_rot_z->m[3][3] = 1;
	return (mat_rot_z);
}

t_vec3d	*rotate(t_mat4x4 *mat_rot, t_vec3d *vec3d)
{
	t_vec3d	*coords_rot;

	if (!vec3d)
		return (NULL);
	coords_rot = 0;
	coords_rot = vec3d_coord(coords_rot, 0, 0, 0);
	if (!coords_rot)
		return (NULL);
	multiply_matrix_vector(vec3d, coords_rot, mat_rot);
	vec3d = vec3d_coord_upd(vec3d, coords_rot->x, coords_rot->y, coords_rot->z);
	free(coords_rot);
	return (vec3d);
}
