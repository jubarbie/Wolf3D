/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 16:45:52 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/07 15:20:56 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	move_forward(t_param *param)
{
	t_vector	go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x + go.x)][(int)(CAM_POS->y + go.y)][0] == '0')
		add_vectors(CAM_POS, &go);
}

static void	move_backward(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

static void	move_straff_left(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	rot_vector(&go, -PI / 2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

static void	move_straff_right(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	rot_vector(&go, PI / 2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

int			moves(t_param *param)
{
	if (MOVES & M_STRAFF_L)
		move_straff_left(param);
	if (MOVES & M_STRAFF_R)
		move_straff_right(param);
	if (MOVES & M_FORWARD)
		move_forward(param);
	if (MOVES & M_BACKWARD)
		move_backward(param);
	if (MOVES & M_LEFT)
	{
		rot_vector(CAM_DIR, 0.5 * SPEED);
		rot_vector(SCREEN, 0.5 * SPEED);
	}
	if (MOVES & M_RIGHT)
	{
		rot_vector(CAM_DIR, -0.5 * SPEED);
		rot_vector(SCREEN, -0.5 * SPEED);
	}
	return (0);
}
