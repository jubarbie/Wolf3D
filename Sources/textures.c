/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 09:56:59 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/16 17:03:16 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_textures(t_param *param)
{
	int	i;

	TEXTX = 512;
	TEXSIZEL = TEXTX * (BPP / 8);
	if (!(TEX = malloc(sizeof(t_tex *) * NB_TEX)))
		quit_wolf(param);
	i = -1;
	while (++i < NB_TEX)
		if (!(TEX[i] = malloc(sizeof(t_tex))))
			quit_wolf(param);
	TEX[0]->img = mlx_xpm_file_to_image(MLX, "Img/wall.xpm", &TEXTX, &TEXTX);
	TEX[1]->img = mlx_xpm_file_to_image(MLX, "Img/wall11.xpm", &TEXTX, &TEXTX);
	TEX[2]->img = mlx_xpm_file_to_image(MLX, "Img/wall12.xpm", &TEXTX, &TEXTX);
	TEX[3]->img = mlx_xpm_file_to_image(MLX, "Img/fan.xpm", &TEXTX, &TEXTX);
	TEX[4]->img = mlx_xpm_file_to_image(MLX, "Img/floor1.xpm", &TEXTX, &TEXTX);
	while (--i >= 0)
	{
		TEX[i]->addr = mlx_get_data_addr(TEX[i]->img, &BPP, &TEXSIZEL, &ENDIAN);
	}
}
