/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:49:33 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:49:40 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	verify_pressed(t_screen *screen_data)
{
	int	keycode;

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
	if (!screen_data->mat_rot_x || !screen_data->mat_rot_z)
		clean_exit(screen_data);
	return (0);
}

int	on_press(int keycode, t_screen *screen_data)
{
	if (keycode == A_TOUCH || keycode == S_TOUCH
		|| keycode == D_TOUCH || keycode == W_TOUCH)
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
	if ((keycode == A_TOUCH || keycode == S_TOUCH
			|| keycode == D_TOUCH || keycode == W_TOUCH)
		&& keycode == screen_data->key_press)
		screen_data->key_press = -1;
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_screen *screen_data)
{
	int	up;

	(void)y, (void)x;
	up = 2;
	if ((keycode == 4 && screen_data->fov < 180)
		|| (keycode == 5 && screen_data->fov > 2))
	{
		if (keycode == 4)
			screen_data->fov += up;
		if (keycode == 5)
			screen_data->fov -= up;
		screen_data->proj_type = 1;
		free(screen_data->mat_proj);
		screen_data->mat_proj = projection(screen_data->fov);
	}
	if (!screen_data->mat_proj)
		clean_exit(screen_data);
	return (0);
}

int	default_options(t_screen *screen_data, char *entry)
{
	screen_data->mat_proj = NULL;
	screen_data->mat_rot_x = NULL;
	screen_data->mat_rot_z = NULL;
	screen_data->vectors = parse_map(entry, screen_data);
	screen_data->fov = 90;
	screen_data->z_divisor = 1;
	screen_data->rotation_x = 0;
	screen_data->rotation_z = 0;
	screen_data->key_press = -1;
	screen_data->mat_proj = iso_projection();
	screen_data->proj_type = 0;
	screen_data->mat_rot_x = matrix_rotation_x(0.0);
	screen_data->mat_rot_z = matrix_rotation_z(0.0);
	if (!screen_data->vectors | !screen_data->mat_proj
		|| !screen_data->mat_rot_x || !screen_data->mat_rot_z)
		return (-1);
	return (0);
}
