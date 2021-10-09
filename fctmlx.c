/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fctmlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:12:10 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/09 16:46:55 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fractol	*kg, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < 1200 && y < 900)
		*(int *)&kg->addr[(x * kg->bits_per_pixel >> 3) +
			(y * kg->line_length)] = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}