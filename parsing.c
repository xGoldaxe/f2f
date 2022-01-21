/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:13:48 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/21 18:24:27 by pleveque         ###   ########.fr       */
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

int	*parse_map(char *filename_map)
{
	char	**res;
	char	*content;
	int		i;
	int		*ret;

	content = read_file(filename_map);
	if (!content)
		return (NULL);
	// return (tab_to_int(res));
	res = ft_split(content, ' ');
	i = 0;
	while (res[i])
		++i;
	ret = malloc(sizeof(int *) * (i + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (res[i])
	{
		ret[i] = ft_atoi(res[i]);
		i++;
	}
	//to print
	int y = 0;
	while (y < i)
	{
		printf("{%d}\n", ret[y]);
		y++;
	}
	return (NULL);
}