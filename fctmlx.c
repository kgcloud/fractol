/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fctmlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: canjugun <canjugun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:12:10 by canjugun          #+#    #+#             */
/*   Updated: 2021/10/08 20:29:02 by canjugun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fractol	*kg, int x, int y, int color)
{
	char	*dst;

	dst = kg->addr + (y * kg->line_length + x * (kg->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}