/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:21:50 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/08 21:09:56 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_keycode(int keycode,t_fractol *kg)
{
	printf("%d\n", keycode);
	if(keycode == 69)
	{	
		kg->zoom *= pow(1.001,155.5);
		mlx_loop_hook(kg, julia, kg);
	}
	if(keycode == 78)
		kg->zoom /= pow(1.001,155.5);
	return(1);	
}

void	init(t_fractol *kg)
{
	kg->zoom = 1;
	kg->maxi = 250;
	kg->h = 900;
	kg->w = 1200;
	kg->cre = -0.7;
	kg->cim = 0.27015;
}

void	mandelbrot(t_fractol *kg)
{
	while (kg->y < kg->h)
	{	
		kg->x = 0;
		while (kg->x < kg->w)
		{	
			kg->pr = 1.5 * (kg->x - kg->w /2) / (0.5 * kg->zoom * kg->w) + kg->movex;
			kg->pi = (kg->y - kg->h / 2) / (0.5 * kg->zoom * kg->h) + kg->movey;
			ft_bzero(&kg->m, sizeof(kg->m));
			kg->i = 0;
			while(kg->i < kg->maxi)
			{
				kg->m.oldre = kg->m.newre;
				kg->m.oldim = kg->m.newim;
				kg->m.newre = kg->m.oldre * kg->m.oldre - kg->m.oldim * kg->m.oldim + kg->pr;
				kg->m.newim = 2 * kg->m.oldre * kg->m.oldim + kg->pi;
				if ((kg->m.newre * kg->m.newre + kg->m.newim * kg->m.newim) > 4)
					break;
				kg->i = kg->i + 1;
			}
			kg->couleurs = create_trgb(0, kg->i % 256, 150, 255 * (kg->i < kg->maxi)) / 100;
			if (kg->i != kg->maxi)
				my_mlx_pixel_put(kg, kg->x, kg->y, kg->couleurs);
			else
				my_mlx_pixel_put(kg, kg->x, kg->y, 00000000);
			kg->x = kg->x + 1;
		}
		kg->y = kg->y + 1;
	}
}
 
void	julia(t_fractol *kg)
{	
	while (kg->y < kg->h)
	{
		kg->x = 0;
		while (kg->x < kg->w)
		{
			kg->newre = 1.5 * (kg->x - kg->w / 2) / (0.5 * kg->zoom * kg->w) + kg->movex;
			kg->newim = (kg->y - kg->h / 2) / (0.5 * kg->zoom * kg->h) + kg->movey;
			kg->i = 0;
			while (kg->i < kg->maxi)
			{
				kg->oldre = kg->newre;
				kg->oldim = kg->newim;
				kg->newre = kg->oldre * kg->oldre - kg->oldim * kg->oldim + kg->cre;
				kg->newim = 2 * kg->oldre * kg->oldim + kg->cim;
				if ((kg->newim * kg->newim + kg->newre * kg->newre) > 4)
					break;
				kg->i = kg->i + 1;
			}
			kg->couleurs = create_trgb(0, kg->i % 256, 150, 255 * (kg->i < kg->maxi)) / 100;
			if (kg->i != kg->maxi)
				my_mlx_pixel_put(kg, kg->x, kg->y, kg->couleurs);
			else
				my_mlx_pixel_put(kg, kg->x, kg->y, 00000000);
			kg->x = kg->x + 1;
		}
		kg->y = kg->y + 1;	
	}	
}

int		main(int ac, char **av)
{
	t_fractol	kg;

	ft_bzero(&kg, sizeof(kg));
	init(&kg);
	if (ac == 2)
	{
		kg.mlx = mlx_init();
		kg.mlx_win = mlx_new_window(kg.mlx, 1200, 900, "fractol!");
		kg.img = mlx_new_image(kg.mlx, 1200, 900);
		kg.addr = mlx_get_data_addr(kg.img, &kg.bits_per_pixel, &kg.line_length,
								&kg.endian);
		
		if (ft_strcmp(av[1], "mandelbrot") == 0)
		{	
			kg.movex = -0.5;
			mandelbrot(&kg);	
		}
		else if (ft_strcmp(av[1], "julia") == 0)
			julia(&kg);
		else
			print("./fractol julia or ./fractol mandelbrot");
		mlx_put_image_to_window(kg.mlx, kg.mlx_win, kg.img, 0, 0);
		mlx_key_hook(kg.mlx_win, ft_keycode, &kg);
		mlx_loop(kg.mlx);
	}
	else
		print("./fractol julia or ./fractol mandelbrot");
}
