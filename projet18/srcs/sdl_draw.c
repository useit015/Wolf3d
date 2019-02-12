/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:15:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 18:19:37 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p, t_point q, Uint32 c)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	i = -1;
	pincr.x = p.x < q.x ? 1 : -1;
	pincr.y = p.y < q.y ? 1 : -1;
	dp.x = abs(q.x - p.x);
	dp.y = abs(q.y - p.y);
	error = dp.x / 2;
	while (++i <= dp.x)
	{
		p.x += pincr.x;
		error += dp.y;
		if (error > dp.x)
		{
			error -= dp.x;
			p.y += pincr.y;
		}
		ft_sdl_put_pixel(pixels, p.x, p.y, c);
	}
}

void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p, t_point q, Uint32 c)
{
	t_point		dp;
	t_point		pincr;
	int			error;
	int			i;

	pincr.x = (p.x < q.x) ? 1 : -1;
	pincr.y = (p.y < q.y) ? 1 : -1;
	dp.x = abs(q.x - p.x);
	dp.y = abs(q.y - p.y);
	error = dp.y / 2;
	i = -1;
	while (++i <= dp.y)
	{
		p.y += pincr.y;
		error += dp.x;
		if (error > dp.y)
		{
			error -= dp.y;
			p.x += pincr.x;
		}
		ft_sdl_put_pixel(pixels, p.x, p.y, c);
	}
}

void		ft_sdl_draw_line(Uint32 *pixels, t_point p, t_point q, Uint32 c)
{
	ft_sdl_put_pixel(pixels, p.x, p.y, c);
	ft_sdl_put_pixel(pixels, q.x, q.y, c);
	if (abs(q.x - p.x) >= abs(q.y - p.y))
		ft_sdl_draw_octant1(pixels, p, q, c);
	else
		ft_sdl_draw_octant2(pixels, p, q, c);
}

void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int radius, Uint32 c)
{
	int				d;
	int				y;
	static	int		x = 0;

	d = 3 - (radius << 1);
	y = radius;
	while (y >= x)
	{
		ft_sdl_put_pixel(pixels, co.x + x, co.y + y, c);
		ft_sdl_put_pixel(pixels, co.x + y, co.y + x, c);
		ft_sdl_put_pixel(pixels, co.x - x, co.y + y, c);
		ft_sdl_put_pixel(pixels, co.x - y, co.y + x, c);
		ft_sdl_put_pixel(pixels, co.x + x, co.y - y, c);
		ft_sdl_put_pixel(pixels, co.x + y, co.y - x, c);
		ft_sdl_put_pixel(pixels, co.x - x, co.y - y, c);
		ft_sdl_put_pixel(pixels, co.x - y, co.y - x, c);
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

void		ft_sdl_draw_rect(Uint32 *pixels, t_rect rect, Uint32 c)
{
	int		i;
	int		j;

	i = rect.y - 1;
	while (++i < rect.y + rect.h)
	{
		j = rect.x - 1;
		while (++j < rect.x + rect.w)
			ft_sdl_put_pixel(pixels, j, i, c);
	}
}
