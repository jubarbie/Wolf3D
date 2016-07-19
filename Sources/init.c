/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:19:58 by jubarbie          #+#    #+#             */
/*   Updated: 2016/07/19 16:24:19 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#include "wolf3d.h"

static int	nb_coord(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str != ' ' && (*(str + 1) == '\0' || *(str + 1) == ' '))
			i++;
		str++;
	}
	return (i);
}

char		***create_map(t_param *param, char *file_name)
{
	int		fd;
	char	*line;
	char	***tab;
	int		stop;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	MAP_HEIGHT = 0;
	while ((stop = get_next_line(fd, &line)) > 0)
		MAP_HEIGHT++;
	if (stop == -1 || MAP_HEIGHT == 0)
		exit(EXIT_FAILURE);
	close(fd);
	if (!(tab = malloc(sizeof(char **) * MAP_HEIGHT)) ||
			((fd = open(file_name, O_RDONLY)) == -1))
		exit(EXIT_FAILURE);
	MAP_HEIGHT = 0;
	MAP_WIDTH = 100000000;
	while ((stop = get_next_line(fd, &line)) > 0)
	{
		MAP_WIDTH = (nb_coord(line) < MAP_WIDTH) ? nb_coord(line) : MAP_WIDTH;
		tab[MAP_HEIGHT++] = ft_strsplit(line, ' ');
	}
	if (MAP_WIDTH < 1)
		exit(EXIT_FAILURE);
	close(fd);
	return (tab);
}

void		free_param(t_param *param)
{
	mlx_destroy_image(MLX, IMG);
	MLX = NULL;
	WIN = NULL;
	IMG = NULL;
	free(param);
}

void		init_cam(t_param *param)
{
	CAM_POS = new_vector(17, 15);
	CAM_DIR = new_vector(-1, 0);
	SCREEN = new_vector(0, 0.66);
	RAY_POS = new_vector(0, 0);
	RAY_DIR = new_vector(0, 0);
}

t_param		*init_param(int size_x, int size_y)
{
	t_param	*param;

	if (!(param = (t_param *)malloc(sizeof(t_param))))
		exit(EXIT_FAILURE);
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, size_x, size_y, "Wolf3d");
	WIN_WIDTH = size_x;
	WIN_HEIGHT = size_y;
	BPP = 24;
	SIZELINE = WIN_WIDTH * (BPP / 8);
	IMG = mlx_new_image(MLX, WIN_WIDTH, WIN_HEIGHT);
	IMG_ADDR = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	return (param);
}
