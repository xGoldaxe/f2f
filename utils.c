/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:53:42 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/21 17:06:12 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	define_coord(t_coord *coord, int x, int y)
{
	coord->x = x;
	coord->y = y;
	return (*coord);
}

int	tern(int condition, int a, int b)
{
	if (condition)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	return (tern(a < 0, -a, a));
}
