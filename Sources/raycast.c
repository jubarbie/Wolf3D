/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 11:20:41 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/07 17:17:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

void		draw_line(int x, int y1, int y2, t_param *param)
{
	int				height;
	int				i;
	unsigned int	color;
	int				pix;
	double			wallx;
	int				textx;

	height = (y2 - y1);
	color = hsv_to_rgb(120, 0.3, 0.3 - (WALLDIST / 80 + (float)SIDE / 60));
	y1--;
	i = 0;
	while (++y1 <= y2)
	{
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
		if (MAP[MAPX][MAPY][0] == '2')
		{
			pix = (((int)((i++ + (LINE_H - height) / 2) * TEXTX / LINE_H) *
					TEXSIZEL) + textx * (BPP / 8));
			if (MAP[MAPX][MAPY][0] == '2')
				color = WALL_ADDR[pix] + WALL_ADDR[pix + 1] * 256 +
								WALL_ADDR[pix + 2] * 65536;
		}
		img_put_pixel(param, x, y1, color);
	}
}

void		raycast(t_param *param)
{
	int		x;
	double	draw_start;
	double	draw_end;
	int		dec;

	x = -1;
	//dec = 7 * sin(5 * (CAM_POS->x - CAM_POS->y));
	dec = 0;
	while (++x < WIN_WIDTH)
	{
		init_raycast_param(x, param);
		find_wall(param);
		LINE_H = WIN_HEIGHT / WALLDIST;
		draw_start = (WIN_HEIGHT / 2) - LINE_H / 2;
		draw_end = (WIN_HEIGHT / 2) + LINE_H / 2;
		draw_start = (draw_start < 0) ? 0 : draw_start;
		draw_end = (draw_end >= WIN_HEIGHT) ? WIN_HEIGHT - 1 : draw_end;
		draw_line(x, (int)draw_start, (int)draw_end, param);
	}
}
