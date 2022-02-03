/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:45:57 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	draw_line(t_vec3d *coord1, t_vec3d *coord2,
t_screen *screen_data, int color)
{
	t_vec3d	*tmp_coord1;
	t_vec3d	*tmp_coord2;
	t_coord	r_c1;
	t_coord	r_c2;

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
	tmp_coord1 = project_point(screen_data->mat_proj, tmp_coord1, screen_data);
	tmp_coord2 = project_point(screen_data->mat_proj, tmp_coord2, screen_data);
	if (!tmp_coord1 || !tmp_coord2)
		return (free(tmp_coord1), free(tmp_coord2), -1);
	define_coord(&r_c1, tmp_coord1->x, tmp_coord1->y);
	define_coord(&r_c2, tmp_coord2->x, tmp_coord2->y);
	print_line(r_c1, r_c2,
		&screen_data->img_data, color);
	return (free(tmp_coord1), free(tmp_coord2), 0);
}

void	iterate_coords(t_vec3d *coord1, t_vec3d *coord2, t_screen *s)
{
	int			i;

	i = 0;
	while (s->vectors[i])
	{
		coord1 = vec3d_coord_upd(coord1, s->vectors[i]->x,
				s->vectors[i]->y, s->vectors[i]->z * s->z_divisor);
		if (i / s->map_x < s->map_y - 1)
		{
			coord2 = vec3d_coord_upd(coord2, s->vectors[i + s->map_x]->x,
					s->vectors[i + s->map_x]->y, s->vectors[i + s->map_x]->z
					* s->z_divisor);
			draw_line(coord1, coord2, s, 0x00ffffff);
		}
		if (i % s->map_x < s->map_x - 1)
		{
			coord2 = vec3d_coord_upd(coord2, s->vectors[i + 1]->x,
					s->vectors[i + 1]->y, s->vectors[i + 1]->z * s->z_divisor);
			draw_line(coord1, coord2, s, 0x00ffffff);
		}
		++i;
	}
}

int	render_next_frame(t_screen *screen_data)
{
	t_vec3d		*coords[2];

	clean_screen(screen_data);
	verify_pressed(screen_data);
	coords[0] = 0;
	coords[1] = 0;
	coords[0] = vec3d_coord(coords[0], 0, 0, 0);
	if (!coords[0])
		clean_exit(screen_data);
	coords[1] = vec3d_coord(coords[0], 0, 0, 0);
	if (!coords[1])
	{
		free(coords[0]);
		clean_exit(screen_data);
	}
	iterate_coords(coords[0], coords[1], screen_data);
	free(coords[0]);
	free(coords[1]);
	mlx_put_image_to_window(screen_data->mlx, screen_data->win,
		screen_data->img_data.img, 0, 0);
	return (0);
}
