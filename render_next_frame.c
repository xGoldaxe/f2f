/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:19:02 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/21 17:06:40 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	render_next_frame(t_screen *screen_data)
{
	t_coord	coord1;
	t_coord	coord2;

	print_line(define_coord(&coord1, 0, 0), define_coord(&coord2, 500, 50),
		&screen_data->img_data, 0x00ff00ff);
	mlx_put_image_to_window(screen_data->mlx, screen_data->win,
		screen_data->img_data.img, 0, 0);
	return (0);
}
