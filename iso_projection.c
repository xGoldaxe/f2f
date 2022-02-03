/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:15:08 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:06:34 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4x4	*iso_projection(void)
{
	t_mat4x4	*mat_proj;
	int			x;
	int			y;

	x = 500;
	y = 500;
	mat_proj = malloc(sizeof(t_mat4x4));
	if (!mat_proj)
		return (NULL);
	clean_4(mat_proj);
	mat_proj->m[0][0] = sqrt(2) / 2;
	mat_proj->m[0][1] = -sqrt(2) / 2;
	mat_proj->m[0][2] = x - sqrt(2) / 2 * (x - y);
	mat_proj->m[1][0] = sqrt(6) / 6;
	mat_proj->m[2][1] = sqrt(6) / 6;
	mat_proj->m[3][2] = y - sqrt(6) / 6 * (x + y - 2);
	mat_proj->m[1][0] = sqrt(3) / 3;
	mat_proj->m[2][1] = sqrt(3) / 3;
	mat_proj->m[3][2] = 1 - sqrt(3) / 3 * (x + y + 1);
	return (mat_proj);
}
