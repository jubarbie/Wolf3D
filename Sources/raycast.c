/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 11:20:41 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 11:13:54 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*static void	raycast_floor(int x, t_param *param)
{
	double	distPlayer, currentDist;
	int		y;

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

	distPlayer = 0.0;

	if (DRAW_END < 0) DRAW_END = WIN_HEIGHT;
	y = DRAW_END;
	while (++y < WIN_HEIGHT)
	{
		currentDist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		double weight = (currentDist - distPlayer) / (WALLDIST - distPlayer);

		double currentFloorX = weight * FLOOR_X + (1.0 - weight) * CAM_POS->x;
		double currentFloorY = weight * FLOOR_Y + (1.0 - weight) * CAM_POS->y;

		int floorTexX;
		int floorTexY;
		floorTexX = (int)(currentFloorX * TXW(4)) % TXW(4);
		floorTexY = (int)(currentFloorY * TXW(4)) % TXW(4);
		int pix = floorTexY * TXSZL(4) + floorTexX * (TXBPP(4) / 8);
		unsigned int color = TX_AD(4)[pix] + (TX_AD(4)[pix + 1] << 8) + (TX_AD(4)[pix + 2] << 16);
		int h;
		double s;
		double v;
		rgb_to_hsv(color, &h, &s, &v);
		color = hsv_to_rgb(h, s, v - 0.1 - (currentDist / 40));
		img_put_pixel(param, x, y, color);
	}
}*/

static void	find_wall(t_param *param)
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

static void	init_raycast_param(int x, t_param *param)
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

void		raycast(t_param *param)
{
	int		x;
	double	draw_start;
	int		dec;

	x = -1;
	dec = 7 * sin(5 * (CAM_POS->x - CAM_POS->y));
	while (++x < WIN_WIDTH)
	{
		init_raycast_param(x, param);
		find_wall(param);
		LINE_H = WIN_HEIGHT / WALLDIST;
		draw_start = (WIN_HEIGHT / 2) - LINE_H / 2;
		DRAW_END = (WIN_HEIGHT / 2) + LINE_H / 2;
		draw_start = (draw_start < 0) ? 0 : draw_start;
		DRAW_END = (DRAW_END >= WIN_HEIGHT) ? WIN_HEIGHT - 1 : DRAW_END;
		draw_raycast_line(x, (int)draw_start, (int)DRAW_END, param);
		//raycast_floor(x, param);
	}
}
