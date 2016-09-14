/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 17:01:44 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/14 12:46:19 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static unsigned int	rgb_case1(unsigned int h, double c, double x, double m)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	rgb;

	r = 0;
	g = 0;
	b = 0;
	if (h < 60)
	{
		r = (unsigned int)((c + m) * 255.0);
		g = (unsigned int)((x + m) * 255.0);
		b = (unsigned int)((0 + m) * 255.0);
	}
	else if (h >= 60 && h < 120)
	{
		r = (unsigned int)((x + m) * 255.0);
		g = (unsigned int)((c + m) * 255.0);
		b = (unsigned int)((0 + m) * 255.0);
	}
	rgb = r << 16;
	rgb |= g << 8;
	rgb |= b;
	return (rgb);
}

static unsigned int	rgb_case2(unsigned int h, double c, double x, double m)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	rgb;

	r = 0;
	g = 0;
	b = 0;
	if (h >= 120 && h < 180)
	{
		r = (unsigned int)((0 + m) * 255.0);
		g = (unsigned int)((c + m) * 255.0);
		b = (unsigned int)((x + m) * 255.0);
	}
	else if (h >= 180 && h < 240)
	{
		r = (unsigned int)((0 + m) * 255.0);
		g = (unsigned int)((x + m) * 255.0);
		b = (unsigned int)((c + m) * 255.0);
	}
	rgb = r << 16;
	rgb |= g << 8;
	rgb |= b;
	return (rgb);
}

static unsigned int	rgb_case3(unsigned int h, double c, double x, double m)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	rgb;

	r = 0;
	g = 0;
	b = 0;
	if (h >= 240 && h < 300)
	{
		r = (unsigned int)((x + m) * 255.0);
		g = (unsigned int)((0 + m) * 255.0);
		b = (unsigned int)((c + m) * 255.0);
	}
	else if (h >= 300 && h < 360)
	{
		r = (unsigned int)((c + m) * 255.0);
		g = (unsigned int)((0 + m) * 255.0);
		b = (unsigned int)((x + m) * 255.0);
	}
	rgb = r << 16;
	rgb |= g << 8;
	rgb |= b;
	return (rgb);
}

unsigned int		hsv_to_rgb(unsigned int h, double s, double v)
{
	double			c;
	double			x;
	double			m;

	s = (s < 0) ? 0 : s;
	s = (s > 1) ? 1 : s;
	v = (v < 0) ? 0 : v;
	v = (v > 1) ? 1 : v;
	h = (h > 360) ? 360 : h;
	c = v * s;
	x = c * (1.0 - fabs(fmod((h / 60.0), 2) - 1.0));
	m = v - c;
	if (h < 120)
		return (rgb_case1(h, c, x, m));
	else if (h < 240)
		return (rgb_case2(h, c, x, m));
	else
		return (rgb_case3(h, c, x, m));
}

void				rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v)
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
		*h = (60 * fmod((gp - bp) / delta, 6));
	else if (c_max == gp)
		*h = (60 * ((bp - rp) / delta + 2));
	else if (c_max == bp)
		*h = (60 * ((rp - gp) / delta + 4));
	*s = ((c_max == 0) ? 0 : delta / c_max);
	*v = c_max;
}
