/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 16:45:52 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/06 15:18:46 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_forward(t_param *param)
{
	t_vector	go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x + go.x)][(int)(CAM_POS->y + go.y)][0] == '0')
		add_vectors(CAM_POS, &go);
}

void	move_backward(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

void	move_side_left(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	rot_vector(&go, -PI / 2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

void	move_side_right(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	rot_vector(&go, PI / 2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

int		moves(t_param *param)
{
	if (MOVES & M_STRAFF_L)
		move_side_left(param);
	if (MOVES & M_STRAFF_R)
		move_side_right(param);
	if (MOVES & M_UP)
		move_forward(param);
	if (MOVES & M_DOWN)
		move_backward(param);
	return (0);
}
