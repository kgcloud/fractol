/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:56:46 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/09 16:56:03 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx/mlx.h"

typedef struct s_mandelbrot2{
	double newre; 
	double newim;
	double oldre;
	double oldim;
}				t_m2;

typedef	struct	s_fractol{	
	t_m2	m;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
	void	*mlx_win;
	double pr;
	double pi;
	double cre;
	double cim;
	double newre; 
	double newim;
	double oldim;
	double oldre;
	double movex; 
	double movey;
	double zoom;	
	int couleurs;	
	int maxi;
	int init;
	int h;
	int w;
	int x;
	int	y;
	int	i;
}				t_fractol;


void	julia(t_fractol	*kg);
void	mandelbrot(t_fractol *kg);

void	my_mlx_pixel_put(t_fractol	*kg, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

int		ft_strcmp(char *s1, char *s2);
int		print(char *str);
void	ft_bzero(void *s, size_t n);
void	init(t_fractol *kg);
#endif