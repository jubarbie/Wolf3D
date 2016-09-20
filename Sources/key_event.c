/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:47:10 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/18 22:22:50 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	menu_select(int keycode, t_env *e)
{
	if (keycode == 125 && MENU < 5)
		MENU = (MENU < 4) ? MENU + 1 : 1;
	else if (keycode == 126 && MENU < 5)
		MENU = (MENU > 1) ? MENU - 1 : 4;
	else if (keycode == 36)
	{
		if (MENU == 1)
			MENU = 0;
		else if (MENU == 2)
			MENU = 11;
		else if (MENU == 3)
			quit_wolf(e);
		else if (MENU == 4)
			MENU = 12;
		else if (MENU == 11)
			MENU = 2;
		else if (MENU == 12)
			MENU = 4;
	}
}

static void	move(int keycode, t_env *e)
{
	if (keycode == 43 || keycode == 12)
		MOVES |= M_STRAFF_L;
	else if (keycode == 47 || keycode == 14)
		MOVES |= M_STRAFF_R;
	else if (keycode == 126 || keycode == 13)
		MOVES |= M_FORWARD;
	else if (keycode == 125 || keycode == 1)
		MOVES |= M_BACKWARD;
	else if (keycode == 123 || keycode == 0)
		MOVES |= M_LEFT;
	else if (keycode == 124 || keycode == 2)
		MOVES |= M_RIGHT;
	else if (keycode == 258 || keycode == 257)
		SPEED *= 1.8;
}

int			ft_key_release(int keycode, t_env *e)
{
	if (keycode == 53)
		quit_wolf(e);
	else if (MENU == 0)
	{
		if (keycode == 43 || keycode == 12)
			MOVES ^= M_STRAFF_L;
		else if (keycode == 47 || keycode == 14)
			MOVES ^= M_STRAFF_R;
		else if (keycode == 126 || keycode == 13)
			MOVES ^= M_FORWARD;
		else if (keycode == 125 || keycode == 1)
			MOVES ^= M_BACKWARD;
		else if (keycode == 123 || keycode == 0)
			MOVES ^= M_LEFT;
		else if (keycode == 124 || keycode == 2)
			MOVES ^= M_RIGHT;
		else if (keycode == 258 || keycode == 257)
			SPEED = 1;
	}
	return (0);
}

int			ft_key_press(int keycode, t_env *e)
{
	if (MENU > 0)
		menu_select(keycode, e);
	else
	{
		move(keycode, e);
		if (keycode == 30)
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
		else if (keycode == 35)
		{
			PLAY_IMG = RES_IMG;
			S_PLAY_IMG = S_RES_IMG;
			MENU = 1;
		}
	}
	return (0);
}
