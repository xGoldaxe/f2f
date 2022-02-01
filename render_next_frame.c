/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/01 19:46:35 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_vec3d		*rotate(t_mat4x4 *mat_rot, t_vec3d *vec3d)
{
	t_vec3d *coords_rot = 0;
	
	coords_rot = vec3d_coord(coords_rot, 0, 0, 0);
	multiply_matrix_vector(vec3d, coords_rot, mat_rot);
	vec3d = vec3d_coord_upd(vec3d, coords_rot->x, coords_rot->y, coords_rot->z);
	free(coords_rot);
	return (vec3d);
}

void	draw_point(t_screen *screen_data, float x, float y, float z, t_mat4x4 *mat_rot_x, t_mat4x4 *mat_rot_z)
{
	t_vec3d *coord;

	coord = NULL;
	coord = define_vec3d_coord(coord, x, y, z);
	coord = rotate(mat_rot_z, coord);
	coord = rotate(mat_rot_x, coord);
	coord->z += 3;
	coord = project_point(screen_data->mat_proj, coord);
	my_mlx_pixel_put(&screen_data->img_data, coord->x, coord->y, 0x00ff0000);
	free(coord);
}

void	draw_line(t_vec3d *coord1, t_vec3d *coord2, t_screen *screen_data, int color)
{
	t_vec3d *tmp_coord1;
	t_vec3d *tmp_coord2;

	tmp_coord1 = 0;
	tmp_coord2 = 0;
	tmp_coord1 = vec3d_coord(tmp_coord1, coord1->x, coord1->y, coord1->z);
	tmp_coord2 = vec3d_coord(tmp_coord2, coord2->x, coord2->y, coord2->z);
	tmp_coord1 = rotate(screen_data->mat_rot_z, tmp_coord1);
	tmp_coord2 = rotate(screen_data->mat_rot_z, tmp_coord2);
	tmp_coord1 = rotate(screen_data->mat_rot_x, tmp_coord1);
	tmp_coord2 = rotate(screen_data->mat_rot_x, tmp_coord2);
	tmp_coord1->z += 3;
	tmp_coord2->z += 3;
	////
	tmp_coord1 = project_point(screen_data->mat_proj, tmp_coord1);
	tmp_coord2 = project_point(screen_data->mat_proj, tmp_coord2);
	t_coord r_c1;
	t_coord r_c2;

	define_coord(&r_c1, tmp_coord1->x, tmp_coord1->y);
	define_coord(&r_c2, tmp_coord2->x, tmp_coord2->y);
	print_line(r_c1, r_c2,
		&screen_data->img_data, color);
	free(tmp_coord1);
	free(tmp_coord2);
}

int	render_next_frame(t_screen *screen_data)
{
	t_vec3d			*coords[4];

	clean_screen(screen_data);
	verify_pressed(screen_data);
//===============
	int i = 0;
	coords[0] = 0;
	coords[1] = 0;
	coords[0] = vec3d_coord(coords[0],0,0,0);
	coords[1] = vec3d_coord(coords[0],0,0,0);
	while (screen_data->vectors[i])
	{
		coords[0] = vec3d_coord_upd(coords[0], 
			screen_data->vectors[i]->x, 
			screen_data->vectors[i]->y,
			screen_data->vectors[i]->z * screen_data->z_divisor);
		if (i / screen_data->map_x < screen_data->map_y - 1)
		{
			coords[1] = vec3d_coord_upd(coords[1], 
				screen_data->vectors[i + screen_data->map_x]->x, 
				screen_data->vectors[i + screen_data->map_x]->y,
				screen_data->vectors[i + screen_data->map_x]->z * screen_data->z_divisor);
			draw_line(coords[0], coords[1], screen_data, 0x00ffffff);
		}
		if (i % screen_data->map_x != screen_data->map_x - 1)
		{
			coords[1] = vec3d_coord_upd(coords[1], 
				screen_data->vectors[i + 1]->x, 
				screen_data->vectors[i + 1]->y,
				screen_data->vectors[i + 1]->z * screen_data->z_divisor);
			draw_line(coords[0], coords[1], screen_data, 0x00ffffff);
		}
		++i;
	}
	free(coords[0]);
	free(coords[1]);
	mlx_put_image_to_window(screen_data->mlx, screen_data->win,
		screen_data->img_data.img, 0, 0);
	return (0);
}
