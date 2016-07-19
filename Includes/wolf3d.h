/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 10:48:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/07/19 16:23:07 by jubarbie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include </System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h>
# include <OpenCL/opencl.h>
# include <pthread.h>
# include "mlx.h"
# include "libft.h"

# define MAP_UNIT 10
# define WALL_HEIGHT 100

# define MLX param->mlx
# define WIN param->win
# define WIN_WIDTH param->winWidth
# define WIN_HEIGHT param->winHeight
# define BPP param->bpp
# define SIZELINE param->sizeline
# define ENDIAN param->endian
# define IMG param->img
# define IMG_ADDR param->img_addr
# define MAP param->map
# define MAP_WIDTH param->mapWidth
# define MAP_HEIGHT param->mapHeight
# define CAM_HEIGHT param->camHeight
# define CAM_POS param->camPos
# define CAM_DIR param->camDir
# define SCREEN param->screen
# define SCREEN_X param->screenX
# define RAY_POS param->rayPos
# define RAY_DIR param->rayDir

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_param
{
	void		*mlx;
	void		*win;
	int			winWidth;
	int			winHeight;
	int			bpp;
	int			sizeline;
	int			endian;
	void		*img;
	char		*img_addr;
	char		***map;
	int			mapWidth;
	int			mapHeight;
	double		camHeight;
	t_vector	*camPos;
	t_vector	*camDir;
	t_vector	*screen;
	double		screenX;
	t_vector	*rayPos;
	t_vector	*rayDir;
}				t_param;

typedef	struct	s_pix
{
	int				x;
	int				y;
	unsigned int	color;
}				t_pix;

t_param			*init_param(int size_x, int size_y);
void			free_param(t_param *param);
char        	***create_map(t_param *param, char *file_name);
void			init_cam(t_param *param);

void			img_put_pixel(t_param *param, int x, int y, unsigned int color);

t_vector		*new_vector(double x, double y);
void			free_vector(t_vector *v);
t_vector		*add_vectors(t_vector *v1, t_vector *v2);

void			error_usage(void);
void			error_opt(char opt);

int				ft_key(int keycode, t_param *param);

#endif
