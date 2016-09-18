/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:08:40 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/18 22:28:47 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_menu(t_env *e)
{
	mlx_destroy_image(MLX, TITLE_IMG);
	mlx_destroy_image(MLX, PLAY_IMG);
	mlx_destroy_image(MLX, HOWTO_IMG);
	mlx_destroy_image(MLX, QUIT_IMG);
	mlx_destroy_image(MLX, INFO_IMG);
	mlx_destroy_image(MLX, S_PLAY_IMG);
	mlx_destroy_image(MLX, S_HOWTO_IMG);
	mlx_destroy_image(MLX, S_QUIT_IMG);
	mlx_destroy_image(MLX, S_INFO_IMG);
}

void	menu(t_env *e)
{
	int	x;
	int	y;

	x = (WIN_WIDTH / 2) - 241;
	while (++x < WIN_WIDTH / 2 + 240 && (y = -1))
		while (++y < WIN_HEIGHT)
			img_put_pixel(e, x, y, 0X00060019);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	mlx_put_image_to_window(MLX, WIN, TITLE_IMG, WIN_WIDTH / 2 - TITLE_W / 2,
																			50);
	mlx_put_image_to_window(MLX, WIN,
		MENU == 1 ? S_PLAY_IMG : PLAY_IMG, WIN_WIDTH / 2 - M_W / 2, 300);
	mlx_put_image_to_window(MLX, WIN,
		MENU == 2 ? S_HOWTO_IMG : HOWTO_IMG, WIN_WIDTH / 2 - M_W / 2,
																	300 + M_H);
	mlx_put_image_to_window(MLX, WIN,
		MENU == 3 ? S_QUIT_IMG : QUIT_IMG, WIN_WIDTH / 2 - M_W / 2,
														WIN_HEIGHT - 2 * M_H);
	mlx_put_image_to_window(MLX, WIN,
		MENU == 4 ? S_INFO_IMG : INFO_IMG, WIN_WIDTH / 2 - M_W / 2,
															WIN_HEIGHT - M_H);
}

void	init_menu(t_env *e)
{
	MENU = 1;
	TITLE_IMG = mlx_xpm_file_to_image(MLX, "Img/title.xpm", &TITLE_W, &TITLE_H);
	PLAY_IMG = mlx_xpm_file_to_image(MLX, "Img/play.xpm", &M_W, &M_H);
	HOWTO_IMG = mlx_xpm_file_to_image(MLX, "Img/howto.xpm", &M_W, &M_H);
	QUIT_IMG = mlx_xpm_file_to_image(MLX, "Img/quit.xpm", &M_W, &M_H);
	INFO_IMG = mlx_xpm_file_to_image(MLX, "Img/infos.xpm", &M_W, &M_H);
	RES_IMG = mlx_xpm_file_to_image(MLX, "Img/resume.xpm", &M_W, &M_H);
	S_PLAY_IMG = mlx_xpm_file_to_image(MLX, "Img/play_s.xpm", &M_W, &M_H);
	S_HOWTO_IMG = mlx_xpm_file_to_image(MLX, "Img/howto_s.xpm", &M_W, &M_H);
	S_QUIT_IMG = mlx_xpm_file_to_image(MLX, "Img/quit_s.xpm", &M_W, &M_H);
	S_INFO_IMG = mlx_xpm_file_to_image(MLX, "Img/infos_s.xpm", &M_W, &M_H);
	S_RES_IMG = mlx_xpm_file_to_image(MLX, "Img/resume_s.xpm", &M_W, &M_H);
}
