/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:19:58 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/18 22:29:34 by jubarbie         ###   ########.fr       */
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

void		free_map(t_env *e)
{
	int	i;

	i = -1;
	while (++i < MAP_HEIGHT)
		free(MAP[i]);
	free(MAP);
}

char		***create_map(t_env *e, char *file_name)
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
	close(fd);
	if (!(tab = malloc(sizeof(char **) * MAP_HEIGHT)) ||
	((fd = open(file_name, O_RDONLY)) == -1) || stop == -1 || MAP_HEIGHT == 0)
		exit(EXIT_FAILURE);
	MAP_HEIGHT = 0;
	MAP_WIDTH = 100000000;
	while ((stop = get_next_line(fd, &line)) > 0)
	{
		MAP_WIDTH = (nb_coord(line) < MAP_WIDTH) ? nb_coord(line) : MAP_WIDTH;
		tab[MAP_HEIGHT++] = ft_strsplit(line, ',');
	}
	if (MAP_WIDTH < 1)
		exit(EXIT_FAILURE);
	close(fd);
	return (tab);
}
