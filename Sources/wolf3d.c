/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 20:11:28 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 17:18:25 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	display_map(t_env *e)
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

static int	create_img(t_env *e)
{
	int			i;
	pthread_t	th[NB_TH];
	char		frame[5];

	if (MENU > 0)
		menu(e);
	else
	{
		TIC = clock();
		draw_sky_floor(e);
		i = -1;
		while (++i < NB_TH)
			if (pthread_create(&th[i], NULL, &raycast,
						(void *)(e->param[i])) < 0)
				quit_wolf(e);
		TF = CLOCKS_PER_SEC / (double)(clock() - TIC);
		snprintf(frame, 5, "%f", TF);
		i = -1;
		while (++i < NB_TH)
			(void)pthread_join(th[i], NULL);
		moves(e);
		mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
		mlx_string_put(MLX, WIN, 10, 2, 0x00FFFFFF, frame);
	}
	return (0);
}

void		img_put_pixel(t_env *e, int x, int y, unsigned int color)
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
	IMG_ADDR[y * SIZELINE + x * (BPP / 8) + 3] = (SPEED > 1.5) ? 150 : 20;
}

int			main(int ac, char **av)
{
	int		i;
	t_env	*e;

	e = init_env(1000, 800);
	i = get_options(ac, av, &OPT);
	if (D)
		display_map(e);
	mlx_loop_hook(MLX, create_img, e);
	mlx_hook(WIN, 17, Button1MotionMask, quit_wolf, e);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key_press, e);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_key_release, e);
	mlx_loop(MLX);
	return (0);
}
