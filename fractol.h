/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:56:46 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/07 19:16:09 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <mlx.h>

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

typedef	struct	s_julia{	
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
	int h;
	int w;
	int x;
	int	y;
	int	i;
}				t_julia;

typedef struct s_mandelbrot2{
	double newre; 
	double newim;
	double oldre;
	double oldim;
}				t_m2;

typedef struct s_mandelbrot{
	t_m2	m;
	double pr;
	double pi;
	double zoom; 
	double movex;
	double movey;
	int	couleurs;
	int maxi;
	int h;
	int w;
	int x;
	int	y;
	int	i;	
}				t_mandelbrot;

void	julia(void);
void	mandelbrot(void);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

int	ft_strcmp(char *s1, char *s2);
int	print(char *str);
void	ft_bzero(void *s, size_t n);

#endif