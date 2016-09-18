/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 11:20:41 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/18 23:28:32 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

	param = (t_param *)arg;
	e = ENV;
	x = TH * (WIN_WIDTH / NB_TH) - 1;
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
		raycast_floor(e, param, x);
	}
	pthread_exit(0);
}
