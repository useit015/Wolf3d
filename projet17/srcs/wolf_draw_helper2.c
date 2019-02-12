/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 14:01:57 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 15:03:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_sprite_sort(int *order, float *dist, int n)
{
	int		size;
	int		swapped;
	t_point	p;

	size = n;
	swapped = 0;
	while (size > 1 || swapped)
	{
		size = (size * 10) / 13;
		if (size == 9 || size == 10)
			size = 11;
		if (size < 1)
			size = 1;
		swapped = 0;
		p.x = -1;
		while (++p.x < n - size)
		{
			p.y = p.x + size;
			if ((dist[p.x] < dist[p.y]) && (swapped = 1))
			{
				ft_swap(&dist[p.x], &dist[p.y], sizeof(float));
				ft_swap(&order[p.x], &order[p.y], sizeof(int));
			}
		}
	}
}

void		ft_draw_map(t_wolf *w)
{
	int		i;
	int		j;
	t_rect	rect;
	t_rect	rect2;

	i = -1;
	rect.w = 10;
	rect.h = 10;
	rect2.x = (int)w->player.y * 10 + w->player.y * 2.0;
	rect2.y = (int)w->player.x * 10 + w->player.x * 2.0;
	rect2.w = 10;
	rect2.h = 10;
	ft_sdl_draw_rect(w->pixels, rect2, 0xFF00FF);
	while (++i < w->map.h)
	{
		j = -1;
		while (++j < w->map.w)
		{
			rect.x = j * rect.w + j * 2.0;
			rect.y = i * rect.h + i * 2.0;
			if (w->map.tab[i][j])
				ft_sdl_draw_rect(w->pixels, rect, 0xFF00FFFF);
		}
	}
}

void		ft_wolf_sprite1(t_wolf *w)
{
	w->sprite_screen = (int)((w->w / 2) * (1 + w->sprite_trans.x /
				w->sprite_trans.y));
	w->sprite_size.y = abs((int)(w->h / w->sprite_trans.y));
	w->sp_start.y = -w->sprite_size.y / 2 + w->h / 2;
	w->sp_start.y = (w->sp_start.y < 0) ? 0 : w->sp_start.y;
	w->sp_end.y = w->sprite_size.y / 2 + w->h / 2;
	w->sp_end.y = w->sp_end.y >= w->h ? w->h - 1 : w->sp_end.y;
	w->sprite_size.x = abs((int)(w->h / w->sprite_trans.y));
	w->sp_start.x = -w->sprite_size.x / 2 + w->sprite_screen;
	w->sp_start.x = (w->sp_start.x < 0) ? 0 : w->sp_start.x;
	w->sp_end.x = w->sprite_size.x / 2 + w->sprite_screen;
	w->sp_end.x = w->sp_end.x >= w->w ? w->w - 1 : w->sp_end.x;
	w->temp = (w->sprite_size.y << 7) - (w->h << 7);
}

void		ft_wolf_sprite2(t_wolf *w, int i)
{
	int		j;
	int		k;
	int		d;

	k = w->sp_end.x;
	while (--k > w->sp_start.x - 1)
	{
		w->tex_x = (int)((((k - (-w->sprite_size.x / 2 + w->sprite_screen))
						<< 8) * T_W / w->sprite_size.x) >> 8);
		if (k > 0 && k < w->w && w->sprite_trans.y < w->z_buffer[k])
		{
			j = w->sp_end.y;
			while (--j > w->sp_start.y - 1)
			{
				d = w->temp + (j << 8);
				w->tex_y = ((d * T_H / w->sprite_size.y) >> 8);
				w->color = w->tex2[w->sprite[w->sprite_order[i]].texture].pixels
					[T_W * w->tex_y + w->tex_x];
				if ((w->color & 0x00FFFFFF) != 0)
					w->pixels[j * w->w + k] = w->color;
			}
		}
	}
}

void		ft_wolf_sprite(t_wolf *w)
{
	int		i;

	i = -1;
	while (++i < NB_SPRITES)
	{
		w->sprite_order[i] = i;
		w->sprite_dist[i] = (w->player.x - w->sprite[i].x) * (w->player.x -
				w->sprite[i].x) + (w->player.y - w->sprite[i].y) * (w->player.y
					- w->sprite[i].y);
	}
	ft_sprite_sort(w->sprite_order, w->sprite_dist, NB_SPRITES);
	while (--i >= 0)
	{
		w->sprite_pos.x = w->sprite[w->sprite_order[i]].x - w->player.x;
		w->sprite_pos.y = w->sprite[w->sprite_order[i]].y - w->player.y;
		w->inv_det = 1.0 / (w->cam_plane.x * w->dir.y - w->dir.x *
				w->cam_plane.y);
		w->sprite_trans.x = w->inv_det * (w->dir.y * w->sprite_pos.x -
				w->dir.x * w->sprite_pos.y);
		w->sprite_trans.y = w->inv_det * (-w->cam_plane.y * w->sprite_pos.x
				+ w->cam_plane.x * w->sprite_pos.y);
		ft_wolf_sprite1(w);
		if (w->sprite_trans.y > 0)
			ft_wolf_sprite2(w, i);
	}
}
