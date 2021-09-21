/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:21:50 by canjugun          #+#    #+#             */
/*   Updated: 2021/09/21 17:44:36 by canjugun         ###   ########.fr       */
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

typedef struct	s_fractol{
	double cre;
	double cim;
	double newre;
	double newim;
	double oldre;
	double oldim;
	double zoom;
	double movex;
	double movey;
	int		maxi;
}				t_fractol;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_fractol kg;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 300, "Fractol!");
	img.img = mlx_new_image(mlx, 400, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	kg.zoom = 1;
	kg.movex = 0;
	kg.movey = 0;
	kg.cre = -0.7;
	kg.cim = 0.27015;
	int y = 0;
	int x = 0;
	int h = 400;
	int w = 300;
	while (y < h)
	{
		while(x < w)
		{
			kg.newre = 1.5 * (x - w / 2) / (0.5 * kg.zoom * w) + kg.movex;
			kg.newim = (y - h / 2) / (0,5 * kg.zoom * h) + kg.movey;
			int i;
			i = -1;
			while (i < kg.maxi)
			{
				i++;
				kg.oldre = kg.newre;
				kg.oldim = kg. newim;
				
				kg.newre = kg.oldre * kg.oldre - kg.oldim * kg.oldim + kg.cre;
				kg.newim = 2 * kg.oldre * kg.oldim + kg.cim;
				if((kg.newre * kg.newre + kg.newim * kg.newim) > 4) 
					break;
			}
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}