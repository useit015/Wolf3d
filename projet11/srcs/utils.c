/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:28:08 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/07 21:33:18 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color)
{
	if (y >= 0 && y < SCR_HEIGHT && x >= 0 && x < SCR_WIDTH)
		pixels[y * SCR_WIDTH + x] = color;
}

int		ft_rgb_color(unsigned int r, unsigned int g, unsigned int b)
{
	return (b + (g << 8) + (r << 16));
}

void	ft_setrgb_color(SDL_Color *col, Uint32 color)
{
	col->b = color % 256;
	col->g = (color / 256) % 256;
	col->r = (color / (256 * 256));
	col->a = 255;
}

int		ft_sdl_error(void)
{
	ft_putendl(SDL_GetError());
	return (-1);
}
