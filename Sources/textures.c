/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 09:56:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 11:13:48 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_textures(t_param *param)
{
	int	i;

	if (!(TEX = malloc(sizeof(t_tex *) * NB_TEX)))
		quit_wolf(param);
	i = -1;
	while (++i < NB_TEX)
		if (!(TEX[i] = malloc(sizeof(t_tex))))
			quit_wolf(param);
	TEX[0]->img = mlx_xpm_file_to_image(MLX, "Img/wall.xpm", &TXW(0), &TXW(0));
	TEX[1]->img = mlx_xpm_file_to_image(MLX, "Img/wall11.xpm", &TXW(1), &TXW(1));
	TEX[2]->img = mlx_xpm_file_to_image(MLX, "Img/wall12.xpm", &TXW(2), &TXW(2));
	TEX[3]->img = mlx_xpm_file_to_image(MLX, "Img/fan.xpm", &TXW(3), &TXW(3));
	TEX[4]->img = mlx_xpm_file_to_image(MLX, "Img/floor1.xpm", &TXW(4), &TXW(4));
	while (--i >= 0)
	{
		TEX[i]->addr = mlx_get_data_addr(TEX[i]->img, &TXBPP(i), &TXSZL(i), &ENDIAN);
	}
}
