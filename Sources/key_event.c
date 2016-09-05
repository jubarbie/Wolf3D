/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:47:10 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/05 19:28:15 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	move(int keycode, t_param *param)
{
	if (keycode == 43)
		move_side_left(param);
	else if (keycode == 47)
		move_side_right(param);
	else if (keycode == 126)
		move_forward(param);
	else if (keycode == 125)
		move_backward(param);
	else if (keycode == 123)
	{
		rot_vector(CAM_DIR, 0.1);
		rot_vector(SCREEN, 0.1);
	}
	else if (keycode == 124)
	{
		rot_vector(CAM_DIR, -0.1);
		rot_vector(SCREEN, -0.1);
	}
}

int			ft_key(int keycode, t_param *param)
{
	//printf("key: %d\n", keycode);
	if (keycode == 53)
	{
		free_param(param);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 30)
		SCREEN->y += 0.01;
	else if (keycode == 33)
		SCREEN->y -= 0.01;
	else if (keycode == 27)
		time_vector(CAM_DIR, 1 / 1.1);
	else if (keycode == 24)
		time_vector(CAM_DIR, 1.1);
	else if (keycode == 41)
		SPEED -= (SPEED > 0.2) ? 0.1 : 0;
	else if (keycode == 39)
		SPEED += (SPEED < 5) ? 0.1 : 0;
	else if (keycode == 260)
		CAM_HEIGHT = 1 / 3;
	move(keycode, param);
	return (0);
}
