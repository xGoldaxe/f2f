#include "fdf.h"

void	clean_screen(t_screen *screen_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			my_mlx_pixel_put(&screen_data->img_data, 0 + x,
				0 + y, 0x000000);
			x++;
		}
		y++;
	}
}
