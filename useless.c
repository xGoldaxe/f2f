int print_line(t_img_data *img_data, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	e;

	dx = x2 - x1;
	if (dx != 0)
	{
		if (dx > 0)
		{
			dy = y2 - y1;
			if (dy != 0)
			{
				//1e cadran
				if (dy > 0)
				{
					if (dx > dy)
					{
						e = dx;
						dx = 2 * e;
						dy = dy * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (++x1 == x2)
								return (0);
							e -= dy;
							if (e < 0)
							{
								++y1;
								e += dx;
							}
						}
					}
					else
					{
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (++y1 == y2)
								return (0);
							e -= dx;
							if (e < 0)
							{
								++x1;
								e += dy;
							}
						}
					}
				}
				//4e cadran
				else
				{
					if (dx >= -dy)
					{
						//8e octant
						e = dx;
						dx = 2 * e;
						dy = dy * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (++x1 == x2)
								return (0);
							e += dy;
							if (e < 0)
							{
								--y1;
								e += dx;
							}
						}
					}
					else
					{
						//7e octant
						e = dy;
						dy = e * 2;
						dx = 2 * dx;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (--y1 == y2)
								return (0);
							e += dx;
							if (e > 0)
							{
								++x1;
								e += dy;
							}
						}
					}
				}
			}
			else
			{
				//horinzontal vers la droite
				while (++x1 < x2)
					my_mlx_pixel_put(img_data, x1, y1, color);
				return (0);
			}
		}
		else
		{
			dy = y2 - y1;
			if (dy != 0)
			{
				if (dy > 0)
				{
					//2e cadran
					if (-dx >= dy)
					{
						//4e octant
						e = dx;
						dx = e * 2;
						dy = dy * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (--x1 == x2)
								return (0);
							e += dy;
							if (e >= 0)
							{
								++y1;
								e += dx;
							}
						}
					}
					else
					{
						//3e octant
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (++y1 == y2)
								return (0);
							e += dx;
							if (e <= 0)
							{
								++x1;
								e += dy;
							}
						}
					}
				}
				else
				{
					//3e cadran
					if (dx <= dy)
					{
						//5e octant
						e = dx;
						dy = dy * 2;
						dx = e * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (--x1 == x2)
								return (0);
							e -= dy;
							if (e >= 0)
							{
								--y1;
								e += dx;
							}
						}
					}
					else
					{
						//6e octant
						e = dy;
						dy = e * 2;
						dx = dx * 2;
						while (1)
						{
							my_mlx_pixel_put(img_data, x1, y1, color);
							if (--y1 == y2)
								return (0);
							e -= dx;
							if (e >= 0)
							{
								--x1;
								e += dy;
							}
						}
					}
				}
			}
			else
			{
				//horizontal gauche
				while (--x1 != x2)
					my_mlx_pixel_put(img_data, x1, y1, color);
			}
		}
	}
	else
	{
		dy = y2 - y1;
		if (dy != 0)
		{
			if (dy > 0)
			{
				//vertical haut
				while (++y1 != y2)
				{
					my_mlx_pixel_put(img_data, x1, y1, color);
				}
			}
			else
			{
				//vertical bas
				while (--y1 != y2)
				{
					my_mlx_pixel_put(img_data, x1, y1, color);
				}
			}
		}
	}
	return (-1);
}