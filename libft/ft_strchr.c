/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaures <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:30:54 by avaures           #+#    #+#             */
/*   Updated: 2021/12/03 22:31:17 by avaures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (! *str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}
