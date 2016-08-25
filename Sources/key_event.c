/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:47:10 by jubarbie          #+#    #+#             */
/*   Updated: 2016/08/25 15:25:31 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_key(int keycode, t_param *param)
{
	//printf("key: %d\n", keycode);
	if (keycode == 53)
	{
		free_param(param);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 123)
		CAM_POS->y -= (CAM_POS->y > 1.2 &&
				MAP[(int)CAM_POS->x][(int)(CAM_POS->y - 0.5)][0] == '0') ? 0.1 : 0;
	else if (keycode == 124)
		CAM_POS->y += (CAM_POS->y < MAP_WIDTH - 1) ? 0.1 : 0;
	else if (keycode == 126)
		CAM_POS->x -= (CAM_POS->x > 1.2) ? 0.1 : 0;
	else if (keycode == 125)
		CAM_POS->x += (CAM_POS->x < MAP_HEIGHT - 1) ? 0.1 : 0;
	else if (keycode == 69)
		SCREEN->y += 0.01;
	else if (keycode == 78)
		SCREEN->y -= 0.01;
	return (0);
}
