/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 17:01:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/05 19:55:14 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_min(int a, int b)
{
	return ((a < b) ? a : b);
}

int	ft_max(int a, int b)
{
	return ((a > b) ? a : b);
}

void	rgb_to_hsv(unsigned int rgb, int *h, double *s, double 
*v)
{
	double	c_max;
	double	c_min;
	double	delta;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	double	rp;
	double 	gp;
	double	bp;
	
	b = ((rgb & 0x00FF0000) >> 16);
	g = ((rgb & 0x00FF00) >> 8);
	r = (rgb & 0x00FF);
	rp = (double)r / 255.0;
	gp = (double)g / 255.0;
	bp = (double)b / 255.0;
	c_max = fmax(fmax(rp, gp), bp);
	c_min = fmin(fmin(rp, gp), bp);
	delta = c_max - c_min;
	if (delta == 0)
		*h = 0;
	else if (c_max == rp)
		*h = 60 * fmod((gp - bp) / delta, 6);
	else if (c_max == gp)
		*h = 60 * ((bp - rp) / delta + 2);
	else if (c_max == bp)
		*h = 60 * ((rp - gp) / delta + 4);
	*s = ((c_max == 0) ? 0 : delta / c_max);
	*v = c_max;	
}
