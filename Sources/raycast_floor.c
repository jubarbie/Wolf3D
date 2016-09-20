/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 22:55:19 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 16:44:53 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_raycast_floor(t_param *param)
{
	t_env	*e;

	e = ENV;
	FLOOR_Y = MAPY + WALL_X;
	FLOOR_X = MAPX + WALL_X;
	if (SIDE == 0 && RAY_DIR->x > 0)
		FLOOR_X = MAPX;
	else if (SIDE == 0 && RAY_DIR->x < 0)
		FLOOR_X = MAPX + 1.0;
	else if (SIDE == 1 && RAY_DIR->y > 0)
		FLOOR_Y = MAPY;
	else
		FLOOR_Y = MAPY + 1.0;
	DIST_PLAYER = 0.0;
	DRAW_END = (DRAW_END < 0) ? WIN_HEIGHT : DRAW_END;
}

static void	get_tex_index(t_env *e, t_param *param)
{
	char	c;

	c = MAP[(int)CUR_FLOORX][(int)CUR_FLOORY][0];
	if (c == '/')
		TX = 5;
	else if (c == '.')
		TX = 7;
	else if (c == '+')
		TX = 18;
	else if (c == '-')
		TX = 19;
	else
		TX = 4;
}

static void	raycast_cielling(t_env *e, t_param *param, int x, int y)
{
	int				pix;
	unsigned int	color;
	t_hsv			hsv;
	char			c;

	c = MAP[(int)CUR_FLOORX][(int)CUR_FLOORY][0];
	if (c < '0' && c > '+')
	{
		TX++;
		TX_FLOORX = (int)(CUR_FLOORX * TXW(TX)) % TXW(TX);
		TX_FLOORY = (int)(CUR_FLOORY * TXW(TX)) % TXW(TX);
		pix = (int)TX_FLOORY * TXSZL(TX) + (int)TX_FLOORX * (TXBPP(TX) / 8);
		color = TX_AD(TX)[pix] + (TX_AD(TX)[pix + 1] << 8) +
													(TX_AD(TX)[pix + 2] << 16);
		rgb_to_hsv(color, &(hsv.h), &(hsv.s), &(hsv.v));
		color = hsv_to_rgb(hsv.h - CUR_DIST, hsv.s,
												hsv.v - 0.1 - (CUR_DIST / 40));
		img_put_pixel(e, x, WIN_HEIGHT - y, color);
	}
}

void		raycast_floor(t_env *e, t_param *param, int x)
{
	int				y;
	int				pix;
	unsigned int	color;
	t_hsv			hsv;

	init_raycast_floor(param);
	y = DRAW_END;
	while (++y < WIN_HEIGHT)
	{
		CUR_DIST = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		WEIGHT = (CUR_DIST - DIST_PLAYER) / (WALLDIST - DIST_PLAYER);
		CUR_FLOORX = WEIGHT * FLOOR_X + (1.0 - WEIGHT) * CAM_POS->x;
		CUR_FLOORY = WEIGHT * FLOOR_Y + (1.0 - WEIGHT) * CAM_POS->y;
		get_tex_index(e, param);
		TX_FLOORX = (int)(CUR_FLOORX * TXW(TX)) % TXW(TX);
		TX_FLOORY = (int)(CUR_FLOORY * TXW(TX)) % TXW(TX);
		pix = (int)TX_FLOORY * TXSZL(TX) + (int)TX_FLOORX * (TXBPP(TX) / 8);
		color = TX_AD(TX)[pix] + (TX_AD(TX)[pix + 1] << 8) +
													(TX_AD(TX)[pix + 2] << 16);
		rgb_to_hsv(color, &(hsv.h), &(hsv.s), &(hsv.v));
		color = hsv_to_rgb(hsv.h, hsv.s, hsv.v - 0.1 - (CUR_DIST / 40));
		img_put_pixel(e, x, y, color);
		raycast_cielling(e, param, x, y);
	}
}
