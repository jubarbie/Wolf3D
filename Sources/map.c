/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:19:58 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 20:58:11 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	nb_coord(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str != ',' && (*(str + 1) == '\0' || *(str + 1) == ','))
			i++;
		str++;
	}
	return (i);
}

static int	get_map_height(char *file_name)
{
	int		fd;
	char	*line;
	int		stop;
	int		height;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		exit(EXIT_FAILURE);
	height = 0;
	while ((stop = get_next_line(fd, &line)) > 0)
	{
		height++;
		free(line);
	}
	if (stop == -1 || height == 0)
		exit(EXIT_FAILURE);
	close(fd);
	return (height);
}

void		free_map(t_env *e)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MAP_HEIGHT && (j = -1))
	{
		while (++j < MAP_WIDTH)
			free(MAP[i][j]);
		free(MAP[i]);
	}
	free(MAP);
}

char		***create_map(t_env *e, char *file_name)
{
	int		fd;
	char	*line;
	char	***tab;
	int		stop;

	MAP_HEIGHT = get_map_height(file_name);
	if (!(tab = malloc(sizeof(char **) * MAP_HEIGHT)) ||
									((fd = open(file_name, O_RDONLY)) == -1))
		exit(EXIT_FAILURE);
	MAP_HEIGHT = 0;
	MAP_WIDTH = 100000000;
	while ((stop = get_next_line(fd, &line)) > 0)
	{
		MAP_WIDTH = (nb_coord(line) < MAP_WIDTH) ? nb_coord(line) : MAP_WIDTH;
		tab[MAP_HEIGHT++] = ft_strsplit(line, ',');
		free(line);
	}
	if (MAP_WIDTH < 1)
		exit(EXIT_FAILURE);
	close(fd);
	return (tab);
}
