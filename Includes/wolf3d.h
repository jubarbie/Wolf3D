/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubarbie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 10:48:32 by jubarbie          #+#    #+#             */
/*   Updated: 2016/09/20 19:37:25 by jubarbie         ###   ########.fr       */
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
# define NB_TH 10

# define OPT_REF "d"
# define OPT e->opt
# define D (OPT & (1 << 0))

# define MLX e->mlx
# define WIN e->win
# define WIN_WIDTH e->win_width
# define WIN_HEIGHT e->win_height
# define BPP e->bpp
# define SIZELINE e->sizeline
# define ENDIAN e->endian
# define IMG e->img
# define IMG_ADDR e->img_addr
# define MAP e->map
# define MAP_WIDTH e->map_width
# define MAP_HEIGHT e->map_height

# define TIC e->tic
# define TF e->time_frame

# define MENU e->menu
# define TITLE_IMG e->title_img
# define TITLE_W e->title_w
# define TITLE_H e->title_h
# define M_W e->m_item_w
# define M_H e->m_item_h
# define M_HIW e->m_hi_h
# define M_HIH e->m_hi_w
# define PLAY_IMG e->play_img
# define PLAY_TIMG e->play_img
# define HOWTO_IMG e->howto_img
# define QUIT_IMG e->quit_img
# define INFO_IMG e->info_img
# define RES_IMG e->resume_img
# define S_PLAY_IMG e->s_play_img
# define S_PLAY_TIMG e->s_play_img
# define S_HOWTO_IMG e->s_howto_img
# define S_QUIT_IMG e->s_quit_img
# define S_INFO_IMG e->s_info_img
# define S_RES_IMG e->s_resume_img
# define H_IMG e->h_img
# define I_IMG e->i_img

# define MOVES e->moves
# define SPEED e->speed
# define M_FORWARD (1 << 0)
# define M_BACKWARD (1 << 1)
# define M_LEFT (1 << 2)
# define M_RIGHT (1 << 3)
# define M_STRAFF_L (1 << 4)
# define M_STRAFF_R (1 << 5)

# define CAM_POS e->cam_pos
# define CAM_DIR e->cam_dir
# define SCREEN e->screen
# define SCREEN_X e->screen_x

# define NB_TEX 21
# define TEX e->textures
# define TX_IM(x) TEX[x]->img
# define TX_AD(x) TEX[x]->addr
# define TXW(x) (TEX[x]->width)
# define TXBPP(x) (TEX[x]->bpp)
# define TXSZL(x) (TEX[x]->sizeline)

# define ENV param->env
# define TH param->index
# define RAY_DIR param->ray_dir
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
# define WALL_X param->wall_x
# define DRAW_END param->draw_end
# define FLOOR_X param->floor_x
# define FLOOR_Y param->floor_y
# define TX param->tex_index
# define DIST_PLAYER param->dist_player
# define CUR_DIST param->current_dist
# define WEIGHT param->weight
# define CUR_FLOORX param->current_floor_x
# define CUR_FLOORY param->current_floor_y
# define TX_FLOORX param->tex_floor_x
# define TX_FLOORY param->tex_floor_y

typedef	struct	s_hsv
{
	int		h;
	double	s;
	double	v;
}				t_hsv;

typedef	struct	s_pix
{
	int				x;
	int				y;
	unsigned int	color;
}				t_pix;
typedef struct	s_texture
{
	void		*img;
	char		*addr;
	int			bpp;
	int			width;
	int			sizeline;
}				t_tex;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_env
{
	char			opt;
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
	int				bpp;
	int				sizeline;
	int				endian;
	void			*img;
	char			*img_addr;

	clock_t			tic;
	double			time_frame;

	char			menu;
	void			*title_img;
	int				title_w;
	int				title_h;
	void			*play_img;
	void			*howto_img;
	void			*quit_img;
	void			*info_img;
	void			*resume_img;
	void			*s_play_img;
	void			*s_howto_img;
	void			*s_quit_img;
	void			*s_info_img;
	void			*s_resume_img;
	int				m_item_w;
	int				m_item_h;
	void			*h_img;
	void			*i_img;
	int				m_hi_w;
	int				m_hi_h;

	char			***map;
	int				map_width;
	int				map_height;
	t_tex			**textures;
	double			speed;
	int				moves;

	t_vector		*cam_pos;
	t_vector		*cam_dir;
	t_vector		*screen;
	double			screen_x;

	struct s_param	*param[NB_TH];
}				t_env;

typedef struct	s_param
{
	t_env		*env;
	int			index;

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
	int			draw_end;
	double		wall_x;
	double		floor_x;
	double		floor_y;
	double		dist_player;
	double		current_dist;
	double		weight;
	double		current_floor_x;
	double		current_floor_y;
	int			tex_floor_x;
	int			tex_floor_y;
	int			tex_index;
}				t_param;

int				get_options(int ac, char **av, char *opt);

t_env			*init_env(int size_x, int size_y);
void			free_env(t_env *e);
char			***create_map(t_env *e, char *file_name);
void			free_map(t_env *e);
void			init_textures(t_env *e);
void			free_textures(t_env *e);
t_param			*init_param(t_env *e, int index);
void			free_param(t_param *param);

void			img_put_pixel(t_env *e, int x, int y, unsigned int color);
void			draw_sky_floor(t_env *e);
void			draw_raycast_line(t_param *param, int x, int y1, int y2);
void			*raycast(void *arg);
void			raycast_floor(t_env *e, t_param *param, int x);

t_vector		*new_vector(double x, double y);
void			rot_vector(t_vector *v, double angle);
void			add_vectors(t_vector *v1, t_vector *v2);
void			sub_vectors(t_vector *v1, t_vector *v2);
void			time_vector(t_vector *v, double i);

void			menu(t_env *e);
void			init_menu(t_env *e);
void			free_menu(t_env *e);
int				moves(t_env *e);

int				quit_wolf(t_env *e);
void			error_usage(void);
void			error_opt(char opt);

unsigned int	hsv_to_rgb(unsigned int h, double s, double v);
void			rgb_to_hsv(unsigned int rgb, int *h, double *s, double *v);

int				ft_key_press(int keycode, t_env *e);
int				ft_key_release(int keycode, t_env *e);

#endif
