/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:21:50 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/07 19:33:45 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_mandelbrot	kg;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 900, "mandelbrot!");
	img.img = mlx_new_image(mlx, 1200, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	ft_bzero(&kg, sizeof(kg));
	kg.zoom = 1;
	kg.movex = -0.5; 
	kg.maxi = 300;
	kg.h = 900;
	kg.w = 1200;	
	while (kg.y < kg.h)
	{	
		kg.x = 0;
		while (kg.x < kg.w)
		{	
			kg.pr = 1.5 * (kg.x - kg.w /2) / (0.5 * kg.zoom * kg.w) + kg.movex;
			kg.pi = (kg.y - kg.h / 2) / (0.5 * kg.zoom * kg.h) + kg.movey;
			ft_bzero(&kg.m, sizeof(kg.m));
			kg.i = 0;
			while(kg.i < kg.maxi)
			{
				kg.m.oldre = kg.m.newre;
				kg.m.oldim = kg.m.newim;
				kg.m.newre = kg.m.oldre * kg.m.oldre - kg.m.oldim * kg.m.oldim + kg.pr;
				kg.m.newim = 2 * kg.m.oldre * kg.m.oldim + kg.pi;
				if ((kg.m.newre * kg.m.newre + kg.m.newim * kg.m.newim) > 4)
					break;
				kg.i = kg.i + 1;
			}
			kg.couleurs = create_trgb(0, kg.i % 256, 150, 255 * (kg.i < kg.maxi)) / 100;
			if (kg.i != kg.maxi)
				my_mlx_pixel_put(&img, kg.x, kg.y, kg.couleurs);
			else
				my_mlx_pixel_put(&img, kg.x, kg.y, 00000000);
			kg.x = kg.x + 1;
		}
		kg.y = kg.y + 1;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
 
void	julia(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;
	t_julia	kg;
	
	ft_bzero(&kg, sizeof(kg));
	kg.maxi = 250;
	kg.h = 900;
	kg.w = 1200;
	kg.cre = -0.7;
	kg.cim = 0.27015;
	kg.zoom = 1;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 900, "julia!");
	img.img = mlx_new_image(mlx, 1200, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	while(1)
	{
		while (kg.y < kg.h)
		{
			kg.x = 0;
			while (kg.x < kg.w)
			{
				kg.newre = 1.5 * (kg.x - kg.w / 2) / (0.5 * kg.zoom * kg.w) + kg.movex;
				kg.newim = (kg.y - kg.h / 2) / (0.5 * kg.zoom * kg.h) + kg.movey;
				kg.i = 0;
				while (kg.i < kg.maxi)
				{
					kg.oldre = kg.newre;
					kg.oldim = kg.newim;
					kg.newre = kg.oldre * kg.oldre - kg.oldim * kg.oldim + kg.cre;
					kg.newim = 2 * kg.oldre * kg.oldim + kg.cim;
					if ((kg.newim * kg.newim + kg.newre * kg.newre) > 4)
						break;
					kg.i = kg.i + 1;
				}
				kg.couleurs = create_trgb(0, kg.i % 256, 150, 255 * (kg.i < kg.maxi)) / 100;
				if (kg.i != kg.maxi)
					my_mlx_pixel_put(&img, kg.x, kg.y, kg.couleurs);
				else
					my_mlx_pixel_put(&img, kg.x, kg.y, 00000000);
				kg.x = kg.x + 1;
			}
			kg.y = kg.y + 1;
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}		
}

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "mandelbrot") == 0)
			mandelbrot();	
		else if (ft_strcmp(av[1], "julia") == 0)
			julia();
		else
			print("./fractol julia or ./fractol mandelbrot");
	}
	else
		print("./fractol julia or ./fractol mandelbrot");
}