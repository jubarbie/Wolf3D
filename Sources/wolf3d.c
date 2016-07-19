/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/07/19 16:22:46 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	display_map(t_param *param)
{
	int i;
	int j;

	printf("width: %d\nheight: %d\n", MAP_WIDTH, MAP_HEIGHT);
	j = -1;
	while (++j < MAP_HEIGHT)
	{
		i = -1;
		while (++i < MAP_WIDTH)
		{
			ft_putstr(MAP[j][i]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}


static void	draw_line(int x, int y1, int y2, int color, t_param *param)
{
	while (y1 <= y2)
	{
		img_put_pixel(param, x, y1, color);
		y1++;
	}
}

static void	raycast(t_param *param)
{
	int		x;
	int		mapX;
	int		mapY;
	double	sideDistX;	
	double	sideDistY;
	double	deltaDistX;	
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		SCREEN_X = 2 * x / (double)WIN_WIDTH - 1;
		RAY_POS->x = CAM_POS->x;
		RAY_POS->y = CAM_POS->y;
		RAY_DIR->x = CAM_DIR->x + SCREEN->x * SCREEN_X;
		RAY_DIR->y = CAM_DIR->y + SCREEN->y * SCREEN_X;
		mapX = (int)RAY_POS->x;
		mapY = (int)RAY_POS->y;
		deltaDistX = sqrt(1 + (RAY_DIR->y * RAY_DIR->y) /
				(RAY_DIR->x * RAY_DIR->x));
		deltaDistY = sqrt(1 + (RAY_DIR->x * RAY_DIR->x) /
				(RAY_DIR->y * RAY_DIR->y));
		hit = 0;
		if (RAY_DIR->x < 0)
		{
			stepX = -1;
			sideDistX = (RAY_POS->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - RAY_POS->x) * deltaDistX;
		}
		if (RAY_DIR->y < 0)
		{
			stepY = -1;
			sideDistY = (RAY_POS->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - RAY_POS->y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (MAP[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - RAY_POS->x + (1 - stepX) / 2) / RAY_DIR->x;
		else
			perpWallDist = (mapY - RAY_POS->y + (1 - stepY) / 2) / RAY_DIR->y;
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;
		draw_line(x, drawStart, drawEnd, 0x00FFFFFF, param);
	}
}

static int	create_img(t_param *param)
{
	raycast(param);
	//draw_line(20, 20, 50, 0x00FFFFFF, param);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

void	img_put_pixel(t_param *param, int x, int y, unsigned int color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	b = ((color & 0xFF0000) >> 16);
	g = ((color & 0xFF00) >> 8);
	r = (color & 0xFF);
	IMG_ADDR[y * SIZELINE + x * (BPP / 8)] = r;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 1] = g;
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 2] = b;
}

int			main(void)
{
	t_param		*param;

	param = init_param(512, 384);
	MAP = create_map(param, "Maps/map1.w3d");
	init_cam(param);
	display_map(param);
	mlx_loop_hook(MLX, create_img, param);
	mlx_expose_hook(WIN, create_img, param);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key, param);
	mlx_loop(MLX);
	free_param(param);
	return (0);
}
