/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 13:52:16 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 16:25:11 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	get_pixel_color(t_param *param, int x, int y, int height)
{
	t_hsv			hsv;
	int				pix;
	unsigned int	color;
	t_env			*e;

	e = ENV;
	if (MAP[MAPX][MAPY][0] > '0' && WALLDIST < 25.0)
	{
		pix = (((int)((y + (LINE_H - height + 1) / 2) *
					TXW(TX) / (LINE_H + 1)) * TXSZL(TX)) + x * (TXBPP(TX) / 8));
		color = TX_AD(TX)[pix] + (TX_AD(TX)[pix + 1] << 8) +
													(TX_AD(TX)[pix + 2] << 16);
	}
	else
		color = hsv_to_rgb(120, 0.2, 0.3);
	rgb_to_hsv(color, &(hsv.h), &(hsv.s), &(hsv.v));
	color = hsv_to_rgb(hsv.h, hsv.s, hsv.v - (WALLDIST / 80 + (float)SIDE / 60));
	return (color);
}

static int	get_texture_x(t_env *e, t_param *param)
{
	int		textx;

	if (SIDE == 0)
		WALL_X = CAM_POS->y + WALLDIST * RAY_DIR->y;
	else
		WALL_X = CAM_POS->x + WALLDIST * RAY_DIR->x;
	WALL_X -= floor(WALL_X);
	textx = (int)(WALL_X * (double)(TXW(TX)));
	if (SIDE == 0 && RAY_DIR->x > 0)
		textx = TXW(TX) - textx - 1;
	if (SIDE == 1 && RAY_DIR->y < 0)
		textx = TXW(TX) - textx - 1;
	return (textx);
}

static void	draw_line_h(t_env *e, int y, unsigned int color)
{
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
		img_put_pixel(e, i, y, color);
}

void		draw_sky_floor(t_env *e)
{
	int i;

	i = -1;
	while (++i < WIN_HEIGHT / 2)
		draw_line_h(e, i, hsv_to_rgb(i * 200 / WIN_HEIGHT + 220, 0.7, 0.2));
	while (++i < WIN_HEIGHT)
		draw_line_h(e, i, hsv_to_rgb(150, 0.2, 0 + ((i - WIN_HEIGHT / 2.0) /
																		1000)));
}

void		draw_raycast_line(t_param *param, int x, int y1, int y2)
{
	int		i;
	int		height;
	int		textx;
	t_env	*e;

	height = (y2 - y1);
	e = ENV;
	TX = MAP[MAPX][MAPY][0] - 49;
	if (MAP[MAPX][MAPY][0] > '0')
		textx = get_texture_x(e, param);
	y1--;
	i = 0;
	while (++y1 <= y2)
		img_put_pixel(e, x, y1, get_pixel_color(param, textx, i++, height));
}

void		img_put_pixel(t_env *e, int x, int y, unsigned int color)
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
