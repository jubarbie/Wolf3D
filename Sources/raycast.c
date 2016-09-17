/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 11:20:41 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 16:25:57 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_raycast_floor(t_param *param)
{
	t_env	*e;

	e = ENV;
	if (SIDE == 0 && RAY_DIR->x > 0)
	{
		FLOOR_X = MAPX;
		FLOOR_Y = MAPY + WALL_X;
	}
	else if (SIDE == 0 && RAY_DIR->x < 0)
	{
		FLOOR_X = MAPX + 1.0;
		FLOOR_Y = MAPY + WALL_X;
	}
	else if (SIDE == 1 && RAY_DIR->y > 0)
	{
		FLOOR_X = MAPX + WALL_X;
		FLOOR_Y = MAPY;
	}
	else
	{
		FLOOR_X = MAPX + WALL_X;
		FLOOR_Y = MAPY + 1.0;
	}
}

static void	raycast_floor(t_param *param, int x)
{
	t_env			*e;
	int				y;
	int				pix;
	unsigned int	color;
	t_hsv			hsv;
	int				id;

	e = ENV;
	init_raycast_floor(param);
	DIST_PLAYER = 0.0;
	if (DRAW_END < 0)
		DRAW_END = WIN_HEIGHT;
	y = DRAW_END;
	while (++y < WIN_HEIGHT)
	{
		CUR_DIST = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		WEIGHT = (CUR_DIST - DIST_PLAYER) / (WALLDIST - DIST_PLAYER);
		CUR_FLOORX = WEIGHT * FLOOR_X + (1.0 - WEIGHT) * CAM_POS->x;
		CUR_FLOORY = WEIGHT * FLOOR_Y + (1.0 - WEIGHT) * CAM_POS->y;
		TX_FLOORX = (int)(CUR_FLOORX * TXW(4)) % TXW(4);
		TX_FLOORY = (int)(CUR_FLOORY * TXW(4)) % TXW(4);
		id = (MAP[(int)CUR_FLOORX][(int)CUR_FLOORY][0] == '/') ? 6 : 4;
		pix = (int)TX_FLOORY * TXSZL(id) + (int)TX_FLOORX * (TXBPP(id) / 8);
		color = TX_AD(id)[pix] + (TX_AD(id)[pix + 1] << 8) +
													(TX_AD(id)[pix + 2] << 16);
		rgb_to_hsv(color, &(hsv.h), &(hsv.s), &(hsv.v));
		color = hsv_to_rgb(hsv.h, hsv.s, hsv.v - 0.1 - (CUR_DIST / 40));
		img_put_pixel(e, x, y, color);
		if (MAP[(int)CUR_FLOORX][(int)CUR_FLOORY][0] == '/')
		{
			pix = (int)TX_FLOORY * TXSZL(5) + (int)TX_FLOORX * (TXBPP(5) / 8);
			color = TX_AD(5)[pix] + (TX_AD(5)[pix + 1] << 8) +
													(TX_AD(5)[pix + 2] << 16);
			rgb_to_hsv(color, &(hsv.h), &(hsv.s), &(hsv.v));
			color = hsv_to_rgb(hsv.h, hsv.s, hsv.v - 0.1 - (CUR_DIST / 40));
			img_put_pixel(e, x, WIN_HEIGHT - y, color);
		}
	}
}

static void	find_wall(t_env *e, t_param *param)
{
	char	hit;

	hit = 0;
	while (hit == 0)
	{
		if (DISTX < DISTY)
		{
			DISTX += DDISTX;
			MAPX += STEPX;
			SIDE = 0;
		}
		else
		{
			DISTY += DDISTY;
			MAPY += STEPY;
			SIDE = 1;
		}
		hit = (MAP[MAPX][MAPY][0] > '0') ? 1 : 0;
	}
	if (SIDE == 0)
		WALLDIST = (MAPX - CAM_POS->x + (1 - STEPX) / 2) / RAY_DIR->x;
	else
		WALLDIST = (MAPY - CAM_POS->y + (1 - STEPY) / 2) / RAY_DIR->y;
}

static void	init_raycast_param(t_env *e, t_param *param, int x)
{
	SCREEN_X = 2 * x / (double)WIN_WIDTH - 1;
	RAY_DIR->x = CAM_DIR->x + SCREEN->x * SCREEN_X;
	RAY_DIR->y = CAM_DIR->y + SCREEN->y * SCREEN_X;
	DDISTX = sqrt(1 + (RAY_DIR->y * RAY_DIR->y) / (RAY_DIR->x * RAY_DIR->x));
	DDISTY = sqrt(1 + (RAY_DIR->x * RAY_DIR->x) / (RAY_DIR->y * RAY_DIR->y));
	MAPX = (int)CAM_POS->x;
	MAPY = (int)CAM_POS->y;
	STEPX = (RAY_DIR->x < 0) ? -1 : 1;
	STEPY = (RAY_DIR->y < 0) ? -1 : 1;
	DISTX = (RAY_DIR->x < 0) ? (CAM_POS->x - MAPX) * DDISTX :
		(MAPX + 1.0 - CAM_POS->x) * DDISTX;
	DISTY = (RAY_DIR->y < 0) ? (CAM_POS->y - MAPY) * DDISTY :
		(MAPY + 1.0 - CAM_POS->y) * DDISTY;
}

void		*raycast(void *arg)
{
	int		x;
	double	draw_start;
	t_param	*param;
	t_env	*e;
	//int	dec;

	param = (t_param *)arg;
	e = ENV;
	x = TH * (WIN_WIDTH / NB_TH) - 1;
	//dec = 7 * sin(5 * (CAM_POS->x - CAM_POS->y));
	while (++x < (TH + 1) * WIN_WIDTH / NB_TH)
	{
		init_raycast_param(ENV, param, x);
		find_wall(ENV, param);
		LINE_H = WIN_HEIGHT / WALLDIST;
		draw_start = (WIN_HEIGHT / 2) - LINE_H / 2;
		DRAW_END = (WIN_HEIGHT / 2) + LINE_H / 2;
		draw_start = (draw_start < 0) ? 0 : draw_start;
		DRAW_END = (DRAW_END >= WIN_HEIGHT) ? WIN_HEIGHT - 1 : DRAW_END;
		draw_raycast_line(param, x, (int)draw_start, (int)DRAW_END);
		raycast_floor(param, x);
	}
	pthread_exit(0);
}
