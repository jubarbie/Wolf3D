/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 09:56:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 16:20:08 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_textures(t_env *e)
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

void	init_textures(t_env *e)
{
	int	i;

	if (!(TEX = malloc(sizeof(t_tex *) * NB_TEX)))
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < NB_TEX)
		if (!(TEX[i] = malloc(sizeof(t_tex))))
			exit(EXIT_FAILURE);
	TX_IM(0) = mlx_xpm_file_to_image(MLX, "Img/wall.xpm", &TXW(0), &TXW(0));
	TX_IM(1) = mlx_xpm_file_to_image(MLX, "Img/wall11.xpm", &TXW(1), &TXW(1));
	TX_IM(2) = mlx_xpm_file_to_image(MLX, "Img/wall12.xpm", &TXW(2), &TXW(2));
	TX_IM(3) = mlx_xpm_file_to_image(MLX, "Img/fan.xpm", &TXW(3), &TXW(3));
	TX_IM(4) = mlx_xpm_file_to_image(MLX, "Img/floor1.xpm", &TXW(4), &TXW(4));
	TX_IM(5) = mlx_xpm_file_to_image(MLX, "Img/top1.xpm", &TXW(5), &TXW(5));
	TX_IM(6) = mlx_xpm_file_to_image(MLX, "Img/floor2.xpm", &TXW(6), &TXW(6));
	while (--i >= 0)
		TX_AD(i) = mlx_get_data_addr(TX_IM(i), &TXBPP(i), &TXSZL(i), &ENDIAN);
}
