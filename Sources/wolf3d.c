/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/16 15:50:18 by jubarbie         ###   ########.fr       */
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
	int 	i;

	i = -1;
	while (++i < WIN_HEIGHT / 2)
		draw_line_h(i, hsv_to_rgb(i * 200 / WIN_HEIGHT + 220, 0.7, 0.2), param);
	while (++i < WIN_HEIGHT)
		draw_line_h(i, hsv_to_rgb(150, 0.2, 0 +
					((i - WIN_HEIGHT / 2.0) / 1000)), param);
	raycast(param);
	moves(param);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

int			main(void)
{
	t_param		*param;

	param = init_param(900, 600);
	//display_map(param);
	mlx_loop_hook(MLX, create_img, param);
	mlx_hook(WIN, 17, Button1MotionMask, quit_wolf, param);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, param);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, param);
	mlx_loop(MLX);
	free_param(param);
	return (0);
}
