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
	rot_vector(&go, -PI/2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}

void	move_side_right(t_param *param)
{
	t_vector go;

	go.x = CAM_DIR->x;
	go.y = CAM_DIR->y;
	rot_vector(&go, PI/2);
	time_vector(&go, SPEED);
	if (MAP[(int)(CAM_POS->x - go.x)][(int)(CAM_POS->y - go.y)][0] == '0')
		sub_vectors(CAM_POS, &go);
}
