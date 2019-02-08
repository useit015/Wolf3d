/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2018/12/27 17:52:33 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void		ft_draw(Uint32 *pixels)
{
	t_point p1 = {20, 20};
  	t_point p2 = {500, 600};

	ft_sdl_draw_line(pixels, p1, p2, 0xFF00FF);
	ft_sdl_draw_circle(pixels, p2, 50, 0xFFFFFF);
	ft_sdl_draw_disc(pixels, p2, 50, 0xFFFF00);
}
