/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:00:02 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/03 21:19:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p1, t_point p2, Uint32 color)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	i = -1;
	pincr.x = p1.x < p2.x ? 1 : -1;
	pincr.y = p1.y < p2.y ? 1 : -1;
	dp.x = abs(p2.x - p1.x);
	dp.y = abs(p2.y - p1.y);
	error = dp.x / 2;
	while (++i <= dp.x)
	{
		p1.x += pincr.x;
		error += dp.y;
		if (error > dp.x)
		{
			error -= dp.x;
			p1.y += pincr.y;
		}
		ft_sdl_put_pixel(pixels, p1.x, p1.y, color);
	}
}

void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p1, t_point p2, Uint32 color)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	pincr.x = (p1.x < p2.x) ? 1 : -1;
	pincr.y = (p1.y < p2.y) ? 1 : -1;
	dp.x = abs(p2.x - p1.x);
	dp.y = abs(p2.y - p1.y);
	error = dp.y / 2;
	i = -1;
	while (++i <= dp.y)
	{
		p1.y += pincr.y;
		error += dp.x;
		if (error > dp.y)
		{
			error -= dp.y;
			p1.x += pincr.x;
		}
		ft_sdl_put_pixel(pixels, p1.x, p1.y, color);
	}
}

void		ft_sdl_draw_line(Uint32 *pixels, t_point p1, t_point p2, Uint32 color)
{
	ft_sdl_put_pixel(pixels, p1.x, p1.y, color);
	ft_sdl_put_pixel(pixels, p2.x, p2.y, color);
	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
		ft_sdl_draw_octant1(pixels, p1, p2, color);
	else
		ft_sdl_draw_octant2(pixels, p1, p2,color);
}

void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int radius , Uint32 color)
{
	int		x;
	int		y;
	int		d;

	d = 3 - (radius << 1); 
	x = 0;
	y = radius;
	while (y >= x)
	{
		ft_sdl_put_pixel(pixels, co.x + x, co.y + y, color);
		ft_sdl_put_pixel(pixels, co.x + y, co.y + x, color);
		ft_sdl_put_pixel(pixels, co.x - x, co.y + y, color);
		ft_sdl_put_pixel(pixels, co.x - y, co.y + x, color);
		ft_sdl_put_pixel(pixels, co.x + x, co.y - y, color);
		ft_sdl_put_pixel(pixels, co.x + y, co.y - x, color);
		ft_sdl_put_pixel(pixels, co.x - x, co.y - y, color);
		ft_sdl_put_pixel(pixels, co.x - y, co.y - x, color);
		if (d < 0)
			d = d + (x << 2) + 6;
		else
		{
			d = d + ((x - y) << 2) + 10;
			--y;
		}
		++x;
	}
}

void		ft_sdl_draw_disc(Uint32 *pixels, t_point co, int radius, Uint32 color)
{
	int		d;
	int		x;
	int		y;

	y = radius;
	d = 3 - (radius << 1);
	x = 0;
	while (y >= x)
	{
		ft_sdl_draw_line(pixels,ft_point(co.x - x, co.y - y), ft_point(co.x  + 1 + x, co.y - y), color);
		ft_sdl_draw_line(pixels, ft_point(co.x - x, co.y + y), ft_point(co.x + 1 + x, co.y + y), color);
		ft_sdl_draw_line(pixels, ft_point(co.x - y, co.y - x), ft_point(co.x + 1 + y, co.y - x), color);
		ft_sdl_draw_line(pixels, ft_point(co.x - y, co.y + x), ft_point(co.x + 1 + y, co.y + x), color);
		if (d < 0)
			d = d + (x << 2) + 6;
		else
		{
			d = d + ((x - y) << 2) + 10;
			--y;
		}
		++x;
	}
}

void		ft_sdl_draw_rect(Uint32 *pixels, t_rect rect, Uint32 color)
{
	int		i;
	int		j;

	i = rect.y - 1;
	while (++i < rect.y + rect.h)
	{
		j = rect.x - 1;
		while (++j < rect.x + rect.w)
			ft_sdl_put_pixel(pixels, j, i, color);
	}
}
