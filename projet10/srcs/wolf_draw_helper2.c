/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 05:35:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 16:57:23 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void	ft_sprite_sort(int *order, double *dist, int n)
{
	int		size;
	int		swapped;
	int		i;
	int		j;

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
		i = -1;
		while (++i < n - size)
		{
			j = i + size;
			if (dist[i] < dist[j])
			{
				ft_swap(&dist[j], &dist[i], sizeof(double));
				ft_swap(&order[i],  &order[j], sizeof(int));
				swapped = 1;
			}
		}
	}
}


void		ft_draw_map(t_wolf *w)
{
	int		i = 0;
	int		j = 0;
	t_rect rect;
	t_rect rect2;

	i = -1;
	rect.w = 10;
	rect.h = 10;
			rect2.x = (int) w->player.y * 10 +  w->player.y * 2.0;
			rect2.y =  (int) w->player.x * 10 + w->player.x * 2.0;
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

void		ft_wolf_sprite(t_wolf *w)
{
	int		i;
	int		j;
	int		k;
	int		d;

	i = -1;
	while (++i < NB_SPRITES)
	{
		w->sprite_order[i] = i;
		w->sprite_dist[i] = (w->player.x - w->sprite[i].x) * (w->player.x - w->sprite[i].x) + 
			(w->player.y - w->sprite[i].y) * (w->player.y - w->sprite[i].y);
	}
	ft_sprite_sort(w->sprite_order, w->sprite_dist, NB_SPRITES);
	i = -1;
	while (++i < NB_SPRITES)
	{
		w->sprite_pos.x = w->sprite[w->sprite_order[i]].x - w->player.x;
		w->sprite_pos.y = w->sprite[w->sprite_order[i]].y - w->player.y;
		w->inv_det = 1.0 / (w->cam_plane.x * w->dir.y - w->dir.x * w->cam_plane.y);
		w->sprite_trans.x = w->inv_det * (w->dir.y * w->sprite_pos.x - w->dir.x * w->sprite_pos.y);
		w->sprite_trans.y = w->inv_det * (-w->cam_plane.y * w->sprite_pos.x + w->cam_plane.x * w->sprite_pos.y);
		w->sprite_screen = (int)((w->w / 2) * (1 + w->sprite_trans.x / w->sprite_trans.y));

		w->sprite_size.y = ft_abs((int)(w->h / w->sprite_trans.y));
		w->sp_start.y = -w->sprite_size.y / 2 + w->h / 2;
		if (w->sp_start.y < 0)
			w->sp_start.y = 0;
		w->sp_end.y = w->sprite_size.y / 2 + w->h / 2;
		if (w->sp_end.y >= w->h)
			w->sp_end.y = w->h - 1;

		w->sprite_size.x = ft_abs((int)(w->h / w->sprite_trans.y));
		w->sp_start.x = -w->sprite_size.x / 2 + w->sprite_screen;
		if (w->sp_start.x < 0)
			w->sp_start.x = 0;
		w->sp_end.x = w->sprite_size.x / 2 + w->sprite_screen;
		if (w->sp_end.x >= w->w)
			w->sp_end.x = w->w - 1;
		k = w->sp_start.x - 1;
		while (++k < w->sp_end.x)
		{
			w->tex_x = (int) (256 * (k - (-w->sprite_size.x / 2 + w->sprite_screen)) * TILE_WIDTH / w->sprite_size.x) / 256;
			if (w->sprite_trans.y > 0 && k > 0 && k < w->w && w->sprite_trans.y < w->z_buffer[k])
			{
				j = w->sp_start.y - 1;
				while (++j < w->sp_end.y)
				{
					d = (j) * 256 - w->h * 128 + w->sprite_size.y * 128;
					w->tex_y = ((d * TILE_HEIGHT / w->sprite_size.y) / 256);
					w->color = w->tex2[w->sprite[w->sprite_order[i]].texture].pixels[TILE_WIDTH * w->tex_y + w->tex_x];
					if ((w->color & 0x00FFFFFF)  != 0)
						w->pixels[j * SCR_WIDTH + k] = w->color;
				}	
			}
		}
	}
}


