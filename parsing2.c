/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:48:24 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/04 12:23:45 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	*get_ratio(t_screen *s, float *ratio)
{
	ratio[0] = 1;
	ratio[1] = 1;
	if (s->map_x > s->map_y)
		ratio[1] = (float)s->map_y / (float)s->map_x;
	else
		ratio[0] = (float)s->map_x / (float)s->map_x;
	return (ratio);
}
