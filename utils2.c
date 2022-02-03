/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:00:51 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:54:06 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**read_lines(char *filename_map)
{
	char	**res;
	char	*content;

	content = read_file(filename_map);
	if (content == NULL)
		return (NULL);
	res = ft_split(content, '\n');
	free(content);
	if (!res)
		return (NULL);
	return (res);
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
	readed = read(fd, buf, 1022);
	while (readed > 0)
	{
		buf[readed] = '\0';
		res = ft_realloc_cat(buf, res);
		if (!res)
		{
			close(fd);
			return (NULL);
		}
		readed = read(fd, buf, 1022);
	}
	close(fd);
	return (res);
}
