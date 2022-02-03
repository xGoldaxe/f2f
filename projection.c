/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:59:32 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:43:04 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3d	*define_vec3d_coord(t_vec3d *coord, float x, float y, float z)
{
	coord = malloc(sizeof(t_vec3d));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

void	clean_4(t_mat4x4 *matrix)
{
	int	i;
	int	y;

	i = 0;
	while (i < 4)
	{
		y = 0;
		while (y < 4)
		{
			matrix->m[i][y] = 0;
			++y;
		}
		++i;
	}
}

void	multiply_matrix_vector(t_vec3d *in, t_vec3d *out, t_mat4x4 *mat)
{
	float	w;

	out->x = in->x * mat->m[0][0] + in->y * mat->m[1][0]
		+ in->z * mat->m[2][0] + mat->m[3][0];
	out->y = in->x * mat->m[0][1] + in->y * mat->m[1][1]
		+ in->z * mat->m[2][1] + mat->m[3][1];
	out->z = in->x * mat->m[0][2] + in->y * mat->m[1][2]
		+ in->z * mat->m[2][2] + mat->m[3][2];
	w = in->x * mat->m[0][3] + in->y * mat->m[1][3]
		+ in->z * mat->m[2][3] + mat->m[3][3];
	if (w != 0.0)
	{
		out->x = out->x / w;
		out->y = out->y / w;
		out->z = out->z / w;
	}
}

t_mat4x4	*projection(float f_fov)
{
	float		f_near;
	float		f_far;
	float		f_aspect_ratio;
	float		f_fov_rad;
	t_mat4x4	*mat_proj;

	f_near = 0.1;
	f_far = 2000.0;
	f_aspect_ratio = 1000 / 1000;
	f_fov_rad = 1.0 / tan(f_fov * 0.5 / 180.0 * 3.14159);
	mat_proj = malloc(sizeof(t_mat4x4));
	if (!mat_proj)
		return (NULL);
	clean_4(mat_proj);
	mat_proj->m[0][0] = f_aspect_ratio * f_fov_rad;
	mat_proj->m[1][1] = f_fov_rad;
	mat_proj->m[2][2] = f_far / (f_far - f_near);
	mat_proj->m[3][2] = (-f_far * f_near) / (f_far - f_near);
	mat_proj->m[2][3] = 1.0;
	mat_proj->m[3][3] = 0.0;
	return (mat_proj);
}

t_vec3d	*project_point(t_mat4x4 *mat_proj, t_vec3d *coord,
t_screen *screen_data)
{
	t_vec3d	*projected_coord;

	if (!coord)
		return (NULL);
	projected_coord = NULL;
	projected_coord = define_vec3d_coord(projected_coord, 0, 0, 0);
	if (!projected_coord)
		return (free(coord), NULL);
	multiply_matrix_vector(coord, projected_coord, mat_proj);
	free(coord);
	if (screen_data->proj_type == 0)
	{
		projected_coord->x *= 300;
		projected_coord->y *= 300;
		projected_coord->x += 500;
		projected_coord->y += 0;
	}
	else
	{
		projected_coord->x += 1.0;
		projected_coord->y += 1.0;
		projected_coord->y *= 0.5 * 1000;
		projected_coord->x *= 0.5 * 1000;
	}
	return (projected_coord);
}
