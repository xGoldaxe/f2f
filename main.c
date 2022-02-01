/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 11:51:33 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/01 19:55:59 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	clean_exit_event(t_screen *screen_data);

int	verify_pressed(t_screen *screen_data)
{
	int keycode;

	keycode = screen_data->key_press;
	if (keycode == A_TOUCH || keycode == D_TOUCH)
	{
		free(screen_data->mat_rot_z);
		if (keycode == A_TOUCH)
			screen_data->rotation_z += 0.01;
		else
			screen_data->rotation_z -= 0.01;
		screen_data->mat_rot_z = matrix_rotation_z(screen_data->rotation_z);
	}
	else if (keycode == W_TOUCH || keycode == S_TOUCH)
	{
		free(screen_data->mat_rot_x);
		if (keycode == W_TOUCH)
			screen_data->rotation_x += 0.01;
		else
			screen_data->rotation_x -= 0.01;
		screen_data->mat_rot_x = matrix_rotation_x(screen_data->rotation_x);
	}
	return (0);
}

int	on_press(int keycode, t_screen *screen_data)
{
	if (keycode == A_TOUCH || keycode == S_TOUCH || keycode == D_TOUCH || keycode == W_TOUCH)
		screen_data->key_press = keycode;
	if (keycode == ESCAPE)
		return (clean_exit(screen_data));
	else if (keycode == MINUS_TOUCH && screen_data->z_divisor > -1)
		screen_data->z_divisor -= 0.1;
	else if (keycode == PLUS_TOUCH && screen_data->z_divisor < 1)
		screen_data->z_divisor += 0.1;
	return (0);
}

int	on_release(int keycode, t_screen *screen_data)
{
	(void)keycode;
	screen_data->key_press = -1;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_screen *screen_data)
{
	(void)x;
	(void)y;
	int	up;

	up = 2;
	if (keycode == 4)
	{
		if (screen_data->fov < 180)
		{
			screen_data->fov += up;
			screen_data->mat_proj = projection(screen_data->mat_proj, screen_data->fov);
		}
	}
	else if (keycode == 5)
	{
		if (screen_data->fov > 2)
		{
			screen_data->fov -= up;
			screen_data->mat_proj = projection(screen_data->mat_proj, screen_data->fov);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_screen	screen_data;
	t_mat4x4	mat_proj;

	(void)argc;
	(void)argv;
	screen_data.vectors = parse_map(argv[1], &screen_data);
	screen_data.fov = 90;
	screen_data.z_divisor = 1;
	screen_data.rotation_x = 0;
	screen_data.rotation_z = 0;
	screen_data.key_press = -1;
	screen_data.mat_proj = projection(&mat_proj, screen_data.fov);
	screen_data.mat_rot_x = matrix_rotation_x(0.0);
	screen_data.mat_rot_z = matrix_rotation_z(0.0);
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
	mlx_hook(screen_data.win, 3, 1L << 1, on_release, &screen_data);
	mlx_hook(screen_data.win, 17, 1L << 16, clean_exit_event, &screen_data);
	mlx_mouse_hook(screen_data.win, mouse_hook, &screen_data);
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
	int	i;
	mlx_destroy_image(screen_data->mlx, screen_data->img_data.img);
	mlx_destroy_window(screen_data->mlx, screen_data->win);
	mlx_destroy_display(screen_data->mlx);
	free(screen_data->mlx);

	free(screen_data->mat_rot_x);
	free(screen_data->mat_rot_z);
	i = 0;
	while (screen_data->vectors[i])
	{
		free(screen_data->vectors[i]);
		++i;
	}
	free(screen_data->vectors);
	exit(0);
	return (-1);
}
