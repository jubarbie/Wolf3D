/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/13 10:18:26 by jubarbie         ###   ########.fr       */
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
		draw_line_h(i, hsv_to_rgb(i * 200 / WIN_HEIGHT + 220, 0.7, 0.2), param);
	while (++i < WIN_HEIGHT)
		draw_line_h(i, hsv_to_rgb(150, 0.2, 0 +
					((float)(i - (float)WIN_HEIGHT / 2) / 1000)), param);
	raycast(param);
	moves(param);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
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

int			main(void)
{
	t_param		*param;

	param = init_param(1400, 900);
	MAP = create_map(param, "Maps/map3.w3d");
	init_cam(param);
	//display_map(param);
	mlx_loop_hook(MLX, create_img, param);
	mlx_hook(WIN, 17, Button1MotionMask, quit_wolf, param);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, param);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, param);
	mlx_loop(MLX);
	free_param(param);
	return (0);
}
