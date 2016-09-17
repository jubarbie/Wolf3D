/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 16:21:53 by jubarbie         ###   ########.fr       */
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

static int	create_img(t_env *e)
{
	int			i;
	pthread_t	th[NB_TH];

	draw_sky_floor(e);
	i = -1;
	while (++i < NB_TH)
		if (pthread_create(&th[i], NULL, &raycast, (void *)(e->param[i])) < 0)
			quit_wolf(e);
	i = -1;
	while (++i < NB_TH)
		(void)pthread_join(th[i], NULL);
	moves(e);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

int			main(void)
{
	t_env	*e;

	e = init_env(1200, 800);
	//display_map(param);
	mlx_loop_hook(MLX, create_img, e);
	mlx_hook(WIN, 17, Button1MotionMask, quit_wolf, e);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, e);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, e);
	mlx_loop(MLX);
	return (0);
}
