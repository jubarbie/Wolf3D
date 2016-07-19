/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 13:16:45 by jubarbie          #+#    #+#             */
/*   Updated: 2016/07/19 16:20:09 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		rot_vector(t_vector *v, double a)
{
	v->x = (v->x * cos(a)) + (v->x * sin(a));
	v->y = (v->y * -sin(a)) + (v->y * cos(a));
}



t_vector	*add_vectors(t_vector *v1, t_vector *v2)
{
	return (new_vector(v1->x + v2->x, v1->y + v2->y));
}

void		free_vector(t_vector *v)
{
	if (v != NULL)
		free(v);
}

t_vector	*new_vector(double x, double y)
{
	t_vector *v;

	if ((v = malloc(sizeof(t_vector))) == NULL)
		exit(EXIT_FAILURE);
	v->x = x;
	v->y = y;
	return (v);
}
