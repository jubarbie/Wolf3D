#include "wolf3d.h"

static void    	find_wall(t_param *param)
{
       	char   	hit;

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


static void    	init_raycast_param(int x, t_param *param)
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

void   		draw_line(int x, int y1, int y2, t_param *param)
{
	//int	i;
	int	y1tmp;
	int	height;
	unsigned int color;

	height = (y2 - y1);
	color = hsv_to_rgb(120, 0.3, 0.3 - (WALLDIST / 30 + (float)SIDE / 60));
	y1tmp = y1;
	/*while (--y1tmp >= 0 && ++i < height)	
       		img_put_pixel(param, x, y1tmp, 0x00FFFFFF - height + i);*/
	//i = -1;
       	//if (MAP[MAPX][MAPY][0] == '2')
	//	while (++i < WIN_WIDTH)
	//		img_put_pixel(param, x + i, y1, 0x00FFFFFF);
	while (y1 <= y2)
       	{
       		img_put_pixel(param, x, y1, (y1 - y1tmp == height / 2) ? 0 : color);
       		y1++;
       	}
	/*i = -1;
	while (++y2 < WIN_HEIGHT && ++i < height)
       		img_put_pixel(param, x, y2, hsv_to_rgb(0, 0, 0));*/
		
}

void    	raycast(t_param *param)
{
       	int    	x;
       	double	lineHeight;
       	double	drawStart;
       	double	drawEnd;

       	x = -1;
       	while (++x < WIN_WIDTH)
       	{
       		init_raycast_param(x, param);
       		find_wall(param);
       		lineHeight = (WIN_HEIGHT / WALLDIST);
       		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2 + WALLDIST / 2 - 5 * ft_atoi(MAP[MAPX][MAPY]);
       		drawStart = (drawStart < 0) ? 0 : drawStart;
       		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2 + WALLDIST / 2;
       		drawEnd = (drawEnd >= WIN_HEIGHT) ? WIN_HEIGHT - 1 : drawEnd;
       		draw_line(x, (int)drawStart, (int)drawEnd, param);
       	}
}
