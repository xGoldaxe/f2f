/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_cat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:35:30 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/03 17:06:18 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_strlen_s(char *str)
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
