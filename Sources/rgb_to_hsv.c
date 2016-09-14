/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 17:01:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/13 13:52:06 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v)
{
	double	c_max;
	double	delta;
	double	rp;
	double	gp;
	double	bp;

	bp = ((rgb & 0x00FF0000) >> 16) / 255.0;
	gp = ((rgb & 0x00FF00) >> 8) / 255.0;
	rp = (rgb & 0x00FF) / 255.0;
	c_max = fmax(fmax(rp, gp), bp);
	delta = fmin(fmin(rp, gp), bp);
	delta = c_max - delta;
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
