/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:45:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 15:53:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	ft_wolf_type1(t_wolf *w)
{
	ft_get_wolfcolor(&w->map, w->map_pos.x, w->map_pos.y, &w->color);
	if (w->side == 1)
		w->color >>= 1;
	ft_sdl_draw_line(w->pixels, w->ps, w->pd, w->color);
}

void	ft_wolf_type2(t_wolf *w)
{
	t_point p;

	w->tile_p.x = (int)(w->wall_x * (float)T_W);
	if (!w->side && w->ray_dir.x > 0)
		w->tile_p.x = T_W - w->tile_p.x - 1;
	if (w->side == 1 && w->ray_dir.y < 0)
		w->tile_p.x = T_W - w->tile_p.x - 1;
	p.y = w->ps.y - 1;
	w->tile_num = w->map.tab[w->map_pos.x][w->map_pos.y] - 1;
	p.x = w->x;
	while (++p.y <= w->pd.y)
	{
		w->d = (p.y << 8) - (w->h << 7) + (w->line_height << 7);
		w->tile_p.y = ((w->d * T_H) / w->line_height) >> 8;
		if (w->type == 1)
			w->color = w->tex1[w->tile_num].pixels[w->tile_p.y * T_W +
				w->tile_p.x];
		else
			w->color = w->tex2[w->tile_num].pixels[w->tile_p.y * T_W +
				w->tile_p.x];
		if (w->side == 1)
			w->color = (w->color >> 1) & 8355711;
		w->pixels[p.y * w->w + p.x] = w->color;
	}
}
