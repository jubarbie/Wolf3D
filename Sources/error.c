/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 14:22:35 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/17 16:25:58 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		quit_wolf(t_env *e)
{
	free_env(e);
	exit(EXIT_FAILURE);
	return (0);
}

void	error_usage(void)
{
	ft_putstr("usage: ./wolf3d\n");
	exit(EXIT_FAILURE);
}

void	error_opt(char opt)
{
	ft_putstr("./wolf3d: illegal option -- ");
	ft_putchar(opt);
	ft_putchar('\n');
	error_usage();
}
