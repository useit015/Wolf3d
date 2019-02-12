/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_draw_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 13:24:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 14:16:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void		ft_wolf_dda_helper(t_wolf *w)
{
	w->cam_x = 2.0 * w->x / (double)(SCR_WIDTH) - 1;
	w->ray_dir.x = w->dir.x + w->cam_x * w->cam_plane.x;
	w->ray_dir.y = w->dir.y + w->cam_x * w->cam_plane.y;
	w->delta_dist.x = fabs(1.0 / w->ray_dir.x);
	w->delta_dist.y = fabs(1.0 / w->ray_dir.y);
	w->hit = 0;
	w->ps.x = w->x;
	w->pd.x = w->x;
	w->map_pos.x = (int)w->player.x;
	w->map_pos.y = (int)w->player.y;
	if ((w->ray_dir.x < 0) && (w->step.x = -1))
		w->side_dist.x = (w->player.x - w->map_pos.x) * w->delta_dist.x;
	else 
	{
		w->step.x = 1;
		w->side_dist.x = (w->map_pos.x + 1.0 - w->player.x) * w->delta_dist.x;
	}
	if ((w->ray_dir.y < 0) && (w->step.y = -1))
		w->side_dist.y = (w->player.y - w->map_pos.y) * w->delta_dist.y;
	else
	{
		w->step.y = 1;
		w->side_dist.y = (w->map_pos.y + 1.0 - w->player.y) * w->delta_dist.y;
	}
}

void		ft_wolf_dda(t_wolf *w)
{
	while (!w->hit)
	{
		if (w->side_dist.x < w->side_dist.y)
		{
			w->side_dist.x += w->delta_dist.x;
			w->map_pos.x += w->step.x;
			w->side = 0;
		}
		else
		{
			w->side_dist.y += w->delta_dist.y;
			w->map_pos.y += w->step.y;
			w->side = 1;
		}
		if (w->map.tab[w->map_pos.x][w->map_pos.y] > 0)
			w->hit = 1;
	}
}

void		ft_wolf_end(t_wolf *w)
{
	if (!w->side)
	{
		w->per_wall_dist = (w->map_pos.x - w->player.x + (1.0 - w->step.x) / 2)
			/ w->ray_dir.x;
		w->wall_x = w->player.y + w->per_wall_dist * w->ray_dir.y;
	}
	else
	{
		w->per_wall_dist = (w->map_pos.y - w->player.y + (1.0 - w->step.y) / 2)
			/ w->ray_dir.y;
		w->wall_x = w->player.x + w->per_wall_dist * w->ray_dir.x;
	}
	w->line_height = (int) (w->h / w->per_wall_dist);
	w->ps.y = (-w->line_height / 2 + w->h / 2);
	if (w->ps.y < 0)
		w->ps.y = 0;
	w->pd.y = w->line_height / 2 + w->h / 2;
	if (w->pd.y >= w->h)
		w->pd.y = w->h - 1;
	w->wall_x -= floor(w->wall_x);
	if (w->type == 0)
		ft_wolf_type1(w);
	else
		ft_wolf_type2(w);
	ft_wolf_cell_floor(w);
}

void		ft_wolf_cell_floorh(t_wolf *w)
{
	if (w->side == 0 && w->ray_dir.x > 0)
	{
		w->p_floor.x = w->map_pos.x;
		w->p_floor.y = w->map_pos.y + w->wall_x;
	}
	else if (w->side == 0 && w->ray_dir.x < 0)
	{
		w->p_floor.x = w->map_pos.x + 1.0;
		w->p_floor.y = w->map_pos.y + w->wall_x;
	}
	else if (w->side == 1 && w->ray_dir.y > 0)
	{
		w->p_floor.x = w->map_pos.x + w->wall_x;
		w->p_floor.y = w->map_pos.y;
	}
	else
	{
		w->p_floor.x = w->map_pos.x + w->wall_x;
		w->p_floor.y = w->map_pos.y + 1.0;
	}
	if (w->pd.y < 0)
		w->pd.y = w->h;
}


void		ft_wolf_cell_floor(t_wolf *w)
{
	double	dist_wall;
	double	dist_player;
	double	curr_dist;
	t_point p;

	ft_wolf_cell_floorh(w);
	dist_wall = w->per_wall_dist;
	dist_player = 0.0;
	p.x = w->x;
	if (w->pd.y < 0)
		w->pd.y = w->h;
	p.y = w->pd.y - 1;
	while (++p.y < w->h)
	{
		curr_dist = w->h / (2.0 * p.y - w->h);
		w->weight = (curr_dist - dist_player) / (dist_wall - dist_player);
		w->cur_floor.x = (w->weight * w->p_floor.x + (1.0 - w->weight) * w->player.x);
		w->cur_floor.y = (w->weight * w->p_floor.y + (1.0 - w->weight) * w->player.y);
		w->tile_floor.x = (int)(w->cur_floor.x * TILE_WIDTH) % (TILE_WIDTH);
		w->tile_floor.y = (int)(w->cur_floor.y * TILE_HEIGHT) % (TILE_HEIGHT);
		w->pixels[p.y * w->w + p.x] = ((w->tex1[7].pixels[TILE_WIDTH * w->tile_floor.y + w->tile_floor.x] >> 1 ) & 8355711);
		w->pixels[(w->h - p.y) * w->w + p.x] = w->tex1[7].pixels[TILE_WIDTH * w->tile_floor.y + w->tile_floor.x];
	}
	w->z_buffer[w->x] = w->per_wall_dist;
}


