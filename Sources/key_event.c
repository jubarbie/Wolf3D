/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:47:10 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/07 17:15:51 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	move(int keycode, t_param *param)
{
	if (keycode == 43)
		MOVES |= M_STRAFF_L;
	else if (keycode == 47)
		MOVES |= M_STRAFF_R;
	else if (keycode == 126)
		MOVES |= M_FORWARD;
	else if (keycode == 125)
		MOVES |= M_BACKWARD;
	else if (keycode == 123)
		MOVES |= M_LEFT;
	else if (keycode == 124)
		MOVES |= M_RIGHT;
	else if (keycode == 258)
		SPEED = 0.2;
}

int			ft_key_release(int keycode, t_param *param)
{
	if (keycode == 43)
		MOVES ^= M_STRAFF_L;
	else if (keycode == 47)
		MOVES ^= M_STRAFF_R;
	else if (keycode == 126)
		MOVES ^= M_FORWARD;
	else if (keycode == 125)
		MOVES ^= M_BACKWARD;
	else if (keycode == 123)
		MOVES ^= M_LEFT;
	else if (keycode == 124)
		MOVES ^= M_RIGHT;
	else if (keycode == 258)
		SPEED = 0.1;
	return (0);
}

int			ft_key_press(int keycode, t_param *param)
{
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
