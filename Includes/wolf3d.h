/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 10:48:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/14 11:10:22 by jubarbie         ###   ########.fr       */
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
# include <time.h>
# include "mlx.h"
# include "libft.h"

# define PI 3.141592

# define MLX param->mlx
# define WIN param->win
# define WIN_WIDTH param->win_width
# define WIN_HEIGHT param->win_height
# define BPP param->bpp
# define SIZELINE param->sizeline
# define ENDIAN param->endian
# define IMG param->img
# define IMG_ADDR param->img_addr
# define MAP param->map
# define MAP_WIDTH param->map_width
# define MAP_HEIGHT param->map_height
# define CAM_POS param->cam_pos
# define CAM_DIR param->cam_dir
# define CAM_HEIGHT param->cam_height
# define SCREEN param->screen
# define SCREEN_X param->screen_x
# define RAY_POS param->ray_pos
# define RAY_DIR param->ray_dir
# define MOVES param->moves
# define M_FORWARD (1 << 0)
# define M_BACKWARD (1 << 1)
# define M_LEFT (1 << 2)
# define M_RIGHT (1 << 3)
# define M_STRAFF_L (1 << 4)
# define M_STRAFF_R (1 << 5)

# define DISTX param->side_dist->x
# define DISTY param->side_dist->y
# define DDISTX param->delta_dist->x
# define DDISTY param->delta_dist->y
# define MAPX param->map_x
# define MAPY param->map_y
# define WALLDIST param->prep_wall_dist
# define LINE_H param->line_height
# define STEPX param->step_x
# define STEPY param->step_y
# define SIDE param->side
# define SPEED param->speed
# define WALL param->wall
# define WALL_ADDR param->wall_addr
# define TEXTX param->text_x
# define TEXSIZEL param->tex_sizeline

# define TEX param->textures
# define TX_AD(x) TEX[x]->addr

# define MENU

typedef struct	s_texture
{
	void		*img;
	char		*addr;
}				t_tex;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_param
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	int			bpp;
	int			sizeline;
	int			endian;
	void		*img;
	char		*img_addr;

	char		***map;
	int			map_width;
	int			map_height;

	double		cam_height;
	t_vector	*cam_pos;
	t_vector	*cam_dir;
	t_vector	*screen;
	double		screen_x;
	t_vector	*ray_pos;
	t_vector	*ray_dir;

	t_vector	*side_dist;
	t_vector	*delta_dist;
	double		prep_wall_dist;
	double		line_height;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	char		side;
	double		speed;
	int			text_x;
	int			tex_sizeline;
	void		*wall;
	char		*wall_addr;
	char		moves;
	t_tex		**textures;

	char		menu;
}				t_param;

typedef	struct	s_pix
{
	int				x;
	int				y;
	unsigned int	color;
}				t_pix;

t_param			*init_param(int size_x, int size_y);
void			free_param(t_param *param);
char			***create_map(t_param *param, char *file_name);
void			init_cam(t_param *param);
void			init_textures(t_param *param);

void			img_put_pixel(t_param *param, int x, int y, unsigned int color);

t_vector		*new_vector(double x, double y);
void			rot_vector(t_vector *v, double angle);
void			add_vectors(t_vector *v1, t_vector *v2);
void			sub_vectors(t_vector *v1, t_vector *v2);
void			time_vector(t_vector *v, double i);

int				moves(t_param *param);

void			raycast(t_param *param);
void			draw_raycast_line(int x, int y1, int y2, t_param *param);

int				quit_wolf(t_param *param);
void			error_usage(void);
void			error_opt(char opt);

unsigned int	hsv_to_rgb(unsigned int h, double s, double v);
void			rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v);
void			draw_line_h(int y, unsigned int color, t_param *param);

int				ft_key_press(int keycode, t_param *param);
int				ft_key_release(int keycode, t_param *param);

#endif
