/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:51:33 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/23 12:28:12 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	clean_exit_event(t_screen *screen_data);

int	on_press(int keycode, t_screen *screen_data)
{
	if (keycode == ESCAPE)
		return (clean_exit(screen_data));
	return (0);
}

int	main(int argc, char **argv)
{
	t_screen	screen_data;
	t_mat4x4	mat_proj;

	(void)argc;
	(void)argv;
	// screen_data.map_data = parse_map(argv[1]);
	// if (!screen_data.map_data)
	// 	return (-1);
	screen_data.mat_proj = projection(&mat_proj);
	screen_data.mlx = mlx_init();
	screen_data.win = mlx_new_window(screen_data.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "fdf");
	screen_data.img_data.img = mlx_new_image(screen_data.mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	screen_data.img_data.addr = mlx_get_data_addr(screen_data.img_data.img,
			&screen_data.img_data.bits_per_pixel,
			&screen_data.img_data.line_length,
			&screen_data.img_data.endian);
	mlx_hook(screen_data.win, 2, 1L << 0, on_press, &screen_data);
	mlx_hook(screen_data.win, 17, 1L << 16, clean_exit_event, &screen_data);
	mlx_loop_hook(screen_data.mlx, render_next_frame, &screen_data);
	mlx_loop(screen_data.mlx);
	return (0);
}

static int	clean_exit_event(t_screen *screen_data)
{
	return (clean_exit(screen_data));
}

int	clean_exit(t_screen *screen_data)
{
	mlx_destroy_image(screen_data->mlx, screen_data->img_data.img);
	mlx_destroy_window(screen_data->mlx, screen_data->win);
	mlx_destroy_display(screen_data->mlx);
	free(screen_data->mlx);
	exit(0);
	return (-1);
}
