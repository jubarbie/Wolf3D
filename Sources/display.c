/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 13:52:16 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/14 08:42:56 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	get_pixel_color(int x, int y, int height, t_param *param)
{
	int				h;
	double			s;
	double			v;
	int				pix;
	unsigned int	color;

	if (MAP[MAPX][MAPY][0] > '0' && WALLDIST < 25.0)
	{
		pix = (((int)((y + (LINE_H - height + 1) / 2) *
							TEXTX / (LINE_H + 1)) * TEXSIZEL) + x * (BPP / 8));
		color = WALL_ADDR[pix] + WALL_ADDR[pix + 1] * 256 +
													WALL_ADDR[pix + 2] * 65536;
	}
	else
		color = hsv_to_rgb(120, 0, 0);
	rgb_to_hsv(color, &h, &s, &v);
	color = hsv_to_rgb(h, s, v - (WALLDIST / 80 + (float)SIDE / 60));
	return (color);
}

static int	get_texture_x(t_param *param)
{
	double	wallx;
	int		textx;

	if (SIDE == 0)
		wallx = CAM_POS->y + WALLDIST * RAY_DIR->y;
	else
		wallx = CAM_POS->x + WALLDIST * RAY_DIR->x;
	wallx -= floor(wallx);
	textx = (int)(wallx * (double)(TEXTX));
	if (SIDE == 0 && RAY_DIR->x > 0)
		textx = TEXTX - textx - 1;
	if (SIDE == 1 && RAY_DIR->y < 0)
		textx = TEXTX - textx - 1;
	return (textx);
}

void		draw_raycast_line(int x, int y1, int y2, t_param *param)
{
	int				i;
	int				height;
	int				textx;

	height = (y2 - y1);
	if (MAP[MAPX][MAPY][0] > '0')
		textx = get_texture_x(param);
	y1--;
	i = 0;
	while (++y1 <= y2)
		img_put_pixel(param, x, y1, get_pixel_color(textx, i++, height, param));
}

void		draw_line_h(int y, unsigned int color, t_param *param)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		img_put_pixel(param, i, y, color);
}

void		img_put_pixel(t_param *param, int x, int y, unsigned int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	b = ((color & 0x00FF0000) >> 16);
	g = ((color & 0x00FF00) >> 8);
	r = (color & 0x00FF);
	IMG_ADDR[y * SIZELINE + x * (BPP / 8)] = r;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 1] = g;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 2] = b;
}
