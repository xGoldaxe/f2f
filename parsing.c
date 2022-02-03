/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:13:48 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:58:43 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_z_minmax(t_screen *screen_data, int	*ret)
{
	int	actual_index;

	screen_data->max_z = ret[0];
	screen_data->min_z = ret[0];
	actual_index = 0;
	while (actual_index < (screen_data->map_x * screen_data->map_y))
	{
		if (ret[actual_index] > screen_data->max_z)
			screen_data->max_z = ret[actual_index];
		if (ret[actual_index] < screen_data->min_z)
			screen_data->min_z = ret[actual_index];
		actual_index++;
	}
}

int	get_map_size(char **res, t_screen *screen_data)
{
	int		x;
	int		y;
	char	**line;

	y = 0;
	while (res[y])
		++y;
	line = ft_split(res[0], ' ');
	if (!line)
		return (-1);
	x = 0;
	while (line[x])
		++x;
	screen_data->map_x = x;
	screen_data->map_y = y;
	free_split((void **)line);
	return (0);
}

int	*read_map(char *filename_map, t_screen *screen_data)
{
	char	**res;
	char	**line;
	int		*ret;
	int		i;
	int		line_index;

	res = read_lines(filename_map);
	if (!res || get_map_size(res, screen_data))
		return (NULL);
	ret = malloc(sizeof(int *) * (screen_data->map_x * screen_data->map_y));
	if (!ret)
		return (free_split((void **)res));
	line = ft_split(res[0], ' ');
	if (!line)
		return (free_split((void **)res));
	line_index = 1;
	while (line)
	{
		i = -1;
		while (line[++i])
			ret[i + (screen_data->map_x * (line_index - 1))] = ft_atoi(line[i]);
		free_split((void **)line);
		line = ft_split(res[line_index++], ' ');
	}
	return (free_split((void **)res), ret);
}

void	*generate_vectors(t_screen *s, int *ret)
{
	int		actual_index;
	t_vec3d	*new_vec;
	float	z_divisor;
	float	r[2];

	z_divisor = float_tern((abs(s->min_z) + abs(s->max_z) == 0),
			0, -(1 / (float)(abs(s->min_z) + abs(s->max_z))));
	s->vectors = malloc(sizeof (t_vec3d *) * (s->map_x * s->map_y + 1));
	if (!s->vectors)
		return (NULL);
	actual_index = 0;
	get_ratio(s, r);
	while (actual_index < (s->map_x * s->map_y))
	{
		new_vec = vec3d_coord(new_vec,
				(actual_index % s->map_x) * (r[0] / (s->map_x - 1) * 2) - r[0],
				(actual_index / s->map_x) * (r[1] / (s->map_y - 1) * 2) - r[1],
				(float)ret[actual_index] * z_divisor);
		s->vectors[actual_index] = new_vec;
		if (!new_vec)
			return (free_split((void **)s->vectors));
		actual_index++;
	}
	s->vectors[actual_index] = NULL;
	return (s->vectors);
}

void	*parse_map(char *filename_map, t_screen *screen_data)
{
	int		*ret;

	ret = read_map(filename_map, screen_data);
	if (!ret)
		return (NULL);
	get_z_minmax(screen_data, ret);
	screen_data->vectors = generate_vectors(screen_data, ret);
	free(ret);
	return (screen_data->vectors);
}
