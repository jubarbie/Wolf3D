/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/08/25 15:25:25 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*static void	display_map(t_param *param)
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
}*/

static int	create_img(t_param *param)
{
	int i;

	i = -1;
	while (++i < WIN_HEIGHT / 2)
		draw_line_h(i, hsv_to_rgb(0.0 + (float)i, 1.0, 0.19), param);
	while (++i < WIN_HEIGHT)	
		draw_line_h(i, hsv_to_rgb(150, 2.6, 0 + ((float)(i - (float)WIN_HEIGHT / 2)/ 2000)), param);
	raycast(param);
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

	param = init_param(800, 600);
	MAP = create_map(param, "Maps/map3.w3d");
	init_cam(param);
	//display_map(param);
	mlx_loop_hook(MLX, create_img, param);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key, param);
	mlx_loop(MLX);
	free_param(param);
	return (0);
}
