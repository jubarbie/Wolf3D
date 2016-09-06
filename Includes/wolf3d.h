/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 10:48:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/06 15:18:50 by jubarbie         ###   ########.fr       */
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

# define PI 3.141592

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
# define CAM_POS param->camPos
# define CAM_DIR param->camDir
# define CAM_HEIGHT param->cam_height
# define SCREEN param->screen
# define SCREEN_X param->screenX
# define RAY_POS param->rayPos
# define RAY_DIR param->rayDir
# define MOVES param->moves
# define M_UP (1 << 0)
# define M_DOWN (1 << 1)
# define M_LEFT (1 << 2)
# define M_RIGHT (1 << 3)
# define M_STRAFF_L (1 << 4)
# define M_STRAFF_R (1 << 5)

# define DISTX param->sideDist->x
# define DISTY param->sideDist->y
# define DDISTX param->deltaDist->x
# define DDISTY param->deltaDist->y
# define MAPX param->mapX
# define MAPY param->mapY
# define WALLDIST param->prepWallDist
# define LINE_H param->lineHeight
# define STEPX param->stepX
# define STEPY param->stepY
# define SIDE param->side
# define SPEED param->speed
# define WALL param->wall
# define WALL_ADDR param->wall_addr
# define TEXTX param->text_x
# define TEXSIZEL param->tex_sizeline

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

	double		cam_height;
	t_vector	*camPos;
	t_vector	*camDir;
	t_vector	*screen;
	double		screenX;
	t_vector	*rayPos;
	t_vector	*rayDir;

	t_vector	*sideDist;
	t_vector	*deltaDist;
	double		prepWallDist;
	double		lineHeight;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	char		side;
	double		speed;
	int			text_x;
	int			tex_sizeline;
	void		*wall;
	char		*wall_addr;
	char		moves;
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
void			rot_vector(t_vector *v, double angle);
void			add_vectors(t_vector *v1, t_vector *v2);
void			sub_vectors(t_vector *v1, t_vector *v2);
void			time_vector(t_vector *v, double i);

int				moves(t_param *param);
void			move_forward(t_param *param);
void			move_backward(t_param *param);
void			move_side_left(t_param *param);
void			move_side_right(t_param *param);

void			raycast(t_param *param);
void			draw_line(int x, int y1, int y2, t_param *param);

void			error_usage(void);
void			error_opt(char opt);

unsigned int		hsv_to_rgb(unsigned int h, double s, double v);
void			draw_line_h(int y, unsigned int color, t_param *param);

int				ft_keyPress(int keycode, t_param *param);
int				ft_keyRelease(int keycode, t_param *param);

#endif
