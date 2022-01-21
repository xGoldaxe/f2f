/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:38:52 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/21 17:06:00 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_line(t_coord c0, t_coord c1,
t_img_data *img_data, int color)
{
	t_coord	d;
	t_coord	s;
	int		err;
	int		e2;

	define_coord(&d, ft_abs(c1.x - c0.x), ft_abs(c1.y - c0.y));
	define_coord(&s, tern((c0.x < c1.x), 1, -1), tern((c0.y < c1.y), 1, -1));
	err = tern((d.x > d.y), d.x, -d.y) / 2;
	while (1)
	{
		my_mlx_pixel_put(img_data, c0.x, c0.y, color);
		if (c0.x == c1.x && c0.y == c1.y)
			return ;
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			c0.x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			c0.y += s.y;
		}
	}
}
