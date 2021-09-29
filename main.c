/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:21:50 by canjugun          #+#    #+#             */
/*   Updated: 2021/09/29 19:12:28 by canjugun         ###   ########.fr       */
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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

	
typedef struct s_couleurs {
	int couleurs;
	int r;
	int g;
	int b;
}				t_couleurs;
	
typedef	struct	s_julia{	
	double cre;
	double cim;
	double newre; 
	double newim;
	double oldim;
	double oldre;
	double movex; 
	double movey;
	int maxi;
	int h;
	int w;
	int x;
	int	y;
	int	i;
	double zoom;
}				t_julia;

typedef struct s_mandelbrot{
	double pr;
	double pi;
	double newre; 
	double newim;
	double oldre;
	double oldim;
	double zoom; 
	double movex;
	double movey;
	int maxi;
	int h;
	int w;
}				t_mandelbrot;

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	print(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
	return (-1);
}

int	key_hook(int keycode, t_vars *vars)
{
	return (keycode);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

int	cclose(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	printf("%d\n", keycode);
	return (1);
}

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

/*void	mandelbrot(void)
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
}*/

void	couleurs(t_julia kg, t_couleurs c, t_data img)
{
		if (c.r > 255)
			c.r = 0;
		if (c.g > 255)
			c.g = 0;
		if (c.b > 255)
			c.b = 0;
		if (kg.i != kg.maxi)
		{	
			c.couleurs = create_trgb(0, kg.i % 256, c.g, 255 * (kg.i < kg.maxi));
			my_mlx_pixel_put(&img, kg.x, kg.y, c.couleurs);
		}
		else
			my_mlx_pixel_put(&img, kg.x, kg.y, 00000000);
		c.r++;
		c.g++;
		c.b++;
}

void	julia(t_data img, t_couleurs c)
{
	t_julia	kg;
	
	ft_bzero(&kg, sizeof(0));
	kg.maxi = 250;
	kg.h = 900;
	kg.w = 1200;
	kg.cre = -0.7;
	kg.cim = 0.27015;
	while (kg.y++ < kg.h)
	{
		kg.x = 0;
		while (kg.x++ < kg.w)
		{
			kg.newre = 1.5 * (kg.x - kg.w / 2) / (0.5 * kg.zoom * kg.w) + kg.movex;
			kg.newim = (kg.y - kg.h / 2) / (0.5 * kg.zoom * kg.h) + kg.movey;
			kg.i = 0;
			while (kg.i++ < kg.maxi)
			{
				kg.oldre = kg.newre;
				kg.oldim = kg.newim;
				kg.newre = kg.oldre * kg.oldre - kg.oldim * kg.oldim + kg.cre;
				kg.newim = 2 * kg.oldre * kg.oldim + kg.cim;
				if ((kg.newim * kg.newim + kg.newre * kg.newre) > 4)
					break;
			}
		printf("ye\n");
		couleurs(kg,c, img);
		}
	}
}

void	init(int choise,t_couleurs c)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_vars	vars;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 900, "Fractol!");
	img.img = mlx_new_image(mlx, 1200, 900);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	/*if (choise == 1)
		mandelbrot(img,c);
	else*/
	printf("yo\n");
	julia(img,c);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
		
}

int		main(int ac, char **av)
{
	t_couleurs c;

	c.r = 80;
	c.g = 150;
	c.b = 200;
	if (ac == 2)
	{
		if (ft_strcmp(av[1], "mandelbrot") == 0)
			init(1, c);	
		else if (ft_strcmp(av[1], "julia") == 0)
			init(2,c);
	}
	else
		print("./fractol julia or ./fractol mandelbrot");
}