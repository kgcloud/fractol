/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:21:50 by canjugun          #+#    #+#             */
/*   Updated: 2021/09/27 18:50:56 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	mandelbrot(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 900, "mandelbrot!");
	img.img = mlx_new_image(mlx, 1200, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	int couleurs;
	int r = 80;
	int g = 150;
	int b = 200;	
	double pr, pi;
	double newre, newim, oldre, oldim;
	double zoom = 1, movex = -0.5, movey = 0;
	int maxi = 900;
	int h = 900;
	int w = 1200;
	
	for(int y = 0; y < h; y++)
	{	
		for (int x = 0 ; x < w; x++)
		{	
			pr = 1.5 * (x - w /2) / (0.5 * zoom * w) + movex;
			pi = (y - h / 2) / (0.5 * zoom * h) + movey;
			newre = newim = oldre = oldim = 0;
			int i;
			for(i = 0; i < maxi; i++)
			{
				oldre = newre;
				oldim = newim;
				newre = oldre * oldre - oldim * oldim + pr;
				newim = 2 * oldre * oldim + pi;
				if ((newre * newre + newim * newim) > 4)
					break;
			}
			if (r > 255)
				r = 0;
			if (g > 255)
				g = 0;
			if (b > 255)
				b = 0;
			couleurs = create_trgb(0, r, g, b);
			if (i != maxi)
				my_mlx_pixel_put(&img, x, y, couleurs);
			else
				my_mlx_pixel_put(&img, x, y, 00000000);
			r++;
			g++;
			b++;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

void	julia(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 900, "julia!");
	img.img = mlx_new_image(mlx, 1200, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	int couleurs;
	int r = 80;
	int g = 150;
	int b = 200;
	double cre, cim;
	double newre, newim, oldim, oldre;
	double zoom = 1, movex = 0, movey = 0;
	int maxi = 250;
	int h = 900;
	int w = 1200;

	cre = -0.7;
	cim = 0.27015;
	
	for(int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			newre = 1.5 * (x - w / 2) / (0.5 * zoom * w) + movex;
			newim = (y - h / 2) / (0.5 * zoom * h) + movey;
			int i;
			
			for(i = 0; i < maxi; i++)
			{
				oldre = newre;
				oldim = newim;
				
				newre = oldre * oldre - oldim * oldim +cre;
				newim = 2 * oldre * oldim + cim;
				if ((newim * newim + newre * newre) > 4)
					break;
			}
			if (r > 255)
				r = 0;
			if (g > 255)
				g = 0;
			if (b > 255)
				b = 0;
			if (i != maxi)
			{	
				couleurs = create_trgb(0, i % 256, g, 255 * (i < maxi));
				my_mlx_pixel_put(&img, x, y, couleurs);
			}
			else
				my_mlx_pixel_put(&img, x, y, 00000000);
			r++;
			g++;
			b++;
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int		main(int ac, char **av)
{
	if (av[1][0] == 'm')
		mandelbrot();
	julia();
}
