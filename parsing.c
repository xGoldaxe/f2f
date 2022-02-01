/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:13:48 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/01 19:30:11 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen_s(char *str)
{
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
	return (tern(str != NULL, ft_strlen(str), 0));
}

char	*ft_realloc_cat(char *src, char *dst)
{
	char			*tmp;
	unsigned int	i;

	tmp = malloc(sizeof(char) * (ft_strlen_s(src) + ft_strlen_s(dst) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	if (dst)
	{
		while (dst[i])
		{
			tmp[i] = dst[i];
			i++;
		}
	}
	while (*src)
	{
		tmp[i] = *src;
		i++;
		src++;
	}
	free(dst);
	tmp[i] = '\0';
	return (tmp);
}

char	*read_file(char *filename)
{
	int		fd;
	char	buf[1023];
	char	*res;
	int		readed;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	res = NULL;
	while ((readed = read(fd, buf, 1022)) > 0)
	{
		buf[readed] = '\0';
		res = ft_realloc_cat(buf, res);
		if (!res)
			return (NULL);
	}
	return (res);
}

void	*parse_map(char *filename_map, t_screen *screen_data)
{
	char	**res;
	char	**line;
	char	*content;
	int		i;
	int		*ret;
	int		x;
	int		y;
	int		ret_pos;

	content = read_file(filename_map);
	if (!content)
		return (NULL);
	// ========== counting =========
	res = ft_split(content, '\n');
	free(content);
	y = 0;
	while (res[y])
		++y;
	line = ft_split(res[0], ' ');
	x = 0;
	while (line[x])
		++x;
	screen_data->max_z = ft_atoi(line[0]);
	screen_data->min_z = ft_atoi(line[0]);
	ret = malloc(sizeof(int *) * (x * y));
	//++===========
	ret_pos = 0;
	int	line_index = 0;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			ret[ret_pos] = ft_atoi(line[i]);
			ret_pos++;
			i++;
		}
		free_split(line);
		line = ft_split(res[line_index], ' ');
		line_index++;
	}
	free_split(res);
	screen_data->map_x = x;
	screen_data->map_y = y;
	//////==============
	int actual_index = 0;
	t_vec3d	*new_vec;
	screen_data->vectors = malloc(sizeof (t_vec3d *) * (x * y + 1));
	while (actual_index < (x * y))
	{
		if (ret[actual_index] > screen_data->max_z)
			screen_data->max_z = ret[actual_index];
		if (ret[actual_index] < screen_data->min_z)
			screen_data->min_z = ret[actual_index];
		actual_index++;
	}
	////
	actual_index = 0;
	float	z_divisor;
	if (abs(screen_data->min_z) + abs(screen_data->max_z) == 0)
		z_divisor = 0;
	else
		z_divisor = -(1 / (float)(abs(screen_data->min_z) + abs(screen_data->max_z)));
	while (actual_index < (x * y))
	{
		new_vec = vec3d_coord(new_vec,
			(actual_index % x) * (1 / ((float)x - 1) * 2) -1,
			(actual_index / x) * (1 / ((float)y - 1) * 2) -1,
			(float)ret[actual_index] * z_divisor);
		screen_data->vectors[actual_index] = new_vec;
		actual_index++;
	}
	free(ret);
	screen_data->vectors[actual_index] = NULL;
	return (screen_data->vectors);
}