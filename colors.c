/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:59:35 by pleveque          #+#    #+#             */
/*   Updated: 2021/12/07 16:45:28 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb & (0xff << 24));
}

int	get_r(int trgb)
{
	return ((trgb & 0xff << 16) / 0x010000);
}

int	get_g(int trgb)
{
	return ((trgb & 0xff << 8) / 0x100);
}

int	get_b(int trgb)
{
	return (trgb & 0xff);
}
