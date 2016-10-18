#include "wolf3d.h"

void	light_manage(t_env *e)
{	
	double toc;

	toc = (double)(clock() - TIC) / CLOCKS_PER_SEC;
	if (S)
	{
		if ((double)(TIC - TIC_LUM) / CLOCKS_PER_SEC >= 0.2)
		{
			LUM = (LUM == 1) ? 0.1 : 1;
			TIC_LUM = clock();
		}
	}	
	else
	{
		if (LUM >= 1)
		{
			LUM_ON = 0;
			LUM = 1;
		}
		(LUM > 0 && LUM_ON == 0) ? LUM -= toc * 0.001 : 0;
		if (LUM_ON == 1)
			(LUM <= 1) ?  LUM += toc * 0.1 : 0;	
	}
}
