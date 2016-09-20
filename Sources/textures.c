/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 09:56:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 17:53:56 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_textures_2(t_env *e)
{
	TX_IM(9) = mlx_xpm_file_to_image(MLX, "Img/tab1.xpm", &TXW(9), &TXW(9));
	TX_IM(10) = mlx_xpm_file_to_image(MLX, "Img/tab2.xpm", &TXW(10), &TXW(10));
	TX_IM(11) = mlx_xpm_file_to_image(MLX, "Img/tab3.xpm", &TXW(11), &TXW(11));
	TX_IM(12) = mlx_xpm_file_to_image(MLX, "Img/ever1.xpm", &TXW(12), &TXW(12));
	TX_IM(13) = mlx_xpm_file_to_image(MLX, "Img/ever2.xpm", &TXW(13), &TXW(13));
	TX_IM(14) = mlx_xpm_file_to_image(MLX, "Img/ever3.xpm", &TXW(14), &TXW(14));
	TX_IM(15) = mlx_xpm_file_to_image(MLX, "Img/ever4.xpm", &TXW(15), &TXW(15));
	TX_IM(16) = mlx_xpm_file_to_image(MLX, "Img/box.xpm", &TXW(16), &TXW(16));
	TX_IM(17) = mlx_xpm_file_to_image(MLX, "Img/walld.xpm", &TXW(17), &TXW(17));
	TX_IM(18) = mlx_xpm_file_to_image(MLX, "Img/floor.xpm", &TXW(18), &TXW(18));
	TX_IM(19) = mlx_xpm_file_to_image(MLX, "Img/box.xpm", &TXW(19), &TXW(19));
	TX_IM(20) = mlx_xpm_file_to_image(MLX, "Img/box.xpm", &TXW(20), &TXW(20));
}

void		free_textures(t_env *e)
{
	int	i;

	i = -1;
	while (++i < NB_TEX)
	{
		mlx_destroy_image(MLX, TEX[i]->img);
		TEX[i]->addr = NULL;
	}
	free(TEX);
}

void		init_textures(t_env *e)
{
	int	i;

	if (!(TEX = malloc(sizeof(t_tex *) * NB_TEX)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < NB_TEX)
		if (!(TEX[i] = malloc(sizeof(t_tex))))
			exit(EXIT_FAILURE);
	TX_IM(0) = mlx_xpm_file_to_image(MLX, "Img/wall1.xpm", &TXW(0), &TXW(0));
	TX_IM(1) = mlx_xpm_file_to_image(MLX, "Img/wall11.xpm", &TXW(1), &TXW(1));
	TX_IM(2) = mlx_xpm_file_to_image(MLX, "Img/wall12.xpm", &TXW(2), &TXW(2));
	TX_IM(3) = mlx_xpm_file_to_image(MLX, "Img/fan.xpm", &TXW(3), &TXW(3));
	TX_IM(4) = mlx_xpm_file_to_image(MLX, "Img/grass.xpm", &TXW(4), &TXW(4));
	TX_IM(5) = mlx_xpm_file_to_image(MLX, "Img/floor1.xpm", &TXW(5), &TXW(5));
	TX_IM(6) = mlx_xpm_file_to_image(MLX, "Img/top1.xpm", &TXW(6), &TXW(6));
	TX_IM(7) = mlx_xpm_file_to_image(MLX, "Img/floor2.xpm", &TXW(7), &TXW(7));
	TX_IM(8) = mlx_xpm_file_to_image(MLX, "Img/top2.xpm", &TXW(8), &TXW(8));
	init_textures_2(e);
	while (--i >= 0)
		TX_AD(i) = mlx_get_data_addr(TX_IM(i), &TXBPP(i), &TXSZL(i), &ENDIAN);
}
