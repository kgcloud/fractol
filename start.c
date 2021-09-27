/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 22:39:05 by canjugun          #+#    #+#             */
/*   Updated: 2021/09/26 22:49:38 by canjugun         ###   ########.fr       */
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

int		main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 300, "Fractol!");
	img.img = mlx_new_image(mlx, 400, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	double	x1 = 2.1;
	double	x2 = 0.6;
	double	y1 = -1.2;
	double	y2 = 1.2;
	int		zoom = 100;
	int		imax = 50;

	double image_x = (x2 - x1) * zoom;
	double image_y = (y2 - y1) * zoom;
	
	int i = 0;
	int couleur[imax + 1];
	while (i < imax)
	{
		couleur[i] = 
		i++;
	}
}