#include "wolf3d.h"

unsigned int	hsv_to_rgb(unsigned int h, float s, float v)
{
	float	c;
	float	x;
	float	m;
	unsigned int	r = 0;
	unsigned int	g = 0;
	unsigned int	b = 0;
	unsigned int	rgb;

	s = (s < 0) ? 0 : s;
	s = (s > 1) ? 1 : s;
	v = (v < 0) ? 0 : v;
	v = (v > 1) ? 1 : v;
	h = (h > 360) ? 360 : h;
	c = v * s;
	x = c * (1 - ft_abs((h / 60) % 2 - 1));
	m = v - c;
	rgb = 0x00000000;
	if (h < 60)
	{
		r = (unsigned int)((c + m) * 255);
		g = (unsigned int)((x + m) * 255);
		b = (unsigned int)((0 + m) * 255);
	}
	else if (h >= 60 && h < 120)
	{
		r = (unsigned int)((x + m) * 255);
		g = (unsigned int)((c + m) * 255);
		b = (unsigned int)((0 + m) * 255);
	}
	else if (h >= 120 && h < 180)
	{
		r = (unsigned int)((0 + m) * 255);
		g = (unsigned int)((c + m) * 255);
		b = (unsigned int)((x + m) * 255);
	}
	else if (h >= 180 && h < 240)
	{
		r = (unsigned int)((0 + m) * 255);
		g = (unsigned int)((x + m) * 255);
		b = (unsigned int)((c + m) * 255);
	}
	else if (h >= 240 && h < 300)
	{
		r = (unsigned int)((x + m) * 255);
		g = (unsigned int)((0 + m) * 255);
		b = (unsigned int)((c + m) * 255);
	}
	else if (h >= 300 && h < 360)
	{
		r = (unsigned int)((c + m) * 255);
		g = (unsigned int)((0 + m) * 255);
		b = (unsigned int)((x + m) * 255);
	}
	//printf("(%d,%d,%d)", r, g, b);
	rgb = r << 16;
	rgb = (g << 8) | rgb;
	rgb = b | rgb;
	return (rgb);
}

void	draw_line_h(int y, unsigned int color, t_param *param)
{
	int	i;

	i = -1;
	while(++i < WIN_WIDTH)
		img_put_pixel(param, i, y, color);
}
