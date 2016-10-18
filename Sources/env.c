/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 16:04:31 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 18:06:17 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		free_param(t_param *param)
{
	free(RAY_DIR);
	free(param->side_dist);
	free(param->delta_dist);
	free(param);
}

void		free_env(t_env *e)
{
	int	i;

	free_textures(e);
	free_menu(e);
	free_map(e);
	i = -1;
	while (++i < NB_TH)
		free_param(e->param[i]);
	mlx_destroy_image(MLX, IMG);
	MLX = NULL;
	WIN = NULL;
	IMG = NULL;
	free(CAM_POS);
	free(CAM_DIR);
	free(SCREEN);
	free(e);
}

t_param		*init_param(t_env *e, int index)
{
	t_param	*param;

	if (!(param = malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	ENV = e;
	TH = index;
	RAY_DIR = new_vector(0, 0);
	param->side_dist = new_vector(0, 0);
	param->delta_dist = new_vector(0, 0);
	return (param);
}

t_env		*init_env(int size_x, int size_y)
{
	t_env	*e;
	int		i;

	if (!(e = (t_env *)malloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, size_x, size_y, "Wolf3d");
	WIN_WIDTH = size_x;
	WIN_HEIGHT = size_y;
	MAP = create_map(e, "Maps/map.w3d");
	IMG = mlx_new_image(MLX, WIN_WIDTH, WIN_HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	init_textures(e);
	SPEED = 1;
	MOVES = 0;
	CAM_POS = new_vector(2, 23.5);
	CAM_DIR = new_vector(1, 0);
	SCREEN = new_vector(0, 0.66);
	LUM = 0.1;
	LUM_ON = 0;
	TIC_LUM = clock();
	i = -1;
	while (++i < NB_TH)
		e->param[i] = init_param(e, i);
	init_menu(e);
	return (e);
}
