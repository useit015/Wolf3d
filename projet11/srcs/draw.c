/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 14:15:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_wolf_draw(t_wolf *w)
{
	w->x = -1;
	while (++w->x < SCR_WIDTH)
	{
		ft_wolf_dda_helper(w);
		ft_wolf_dda(w);
		ft_wolf_end(w);
	}
	if (w->help)
		ft_draw_map(w);
	w->old_time = w->curr_time;
	w->curr_time = SDL_GetTicks();
	w->frame_time = (w->curr_time - w->old_time) / 1000.0;
	ft_update_renderer(w->ptr, w->pixels);
	w->player.mv_speed = (w->frame_time) * 5.0;
	w->player.rot_speed = (w->frame_time) * 3.0;
	SDL_Delay(1);
}

void		ft_wolf_keyh(t_wolf *w, t_input *in)
{
	if (in->keys[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->keys[SDL_SCANCODE_T])
		w->type = ++w->type % 3;
	if (in->keys[SDL_SCANCODE_H])
		w->help = ++w->help % 2;
	if (in->keys[SDL_SCANCODE_UP])
	{
		if (!w->map.tab[(int)(w->player.x + w->dir.x * w->player.mv_speed)]\
				[(int)(w->player.y)])
			w->player.x += w->dir.x * w->player.mv_speed;
		if (!w->map.tab[(int)(w->player.x)][(int)(w->player.y + \
					w->dir.y * w->player.mv_speed)])
			w->player.y += w->dir.y * w->player.mv_speed;
	}
}

void		ft_wolf_key(t_wolf *w, t_input *in)
{
	ft_wolf_keyh(w, in);
	if (in->keys[SDL_SCANCODE_DOWN])
	{
		if (!w->map.tab[(int)(w->player.x - w->dir.x * w->player.mv_speed)]\
				[(int)(w->player.y)])
			w->player.x -= w->dir.x * w->player.mv_speed;
		if (!w->map.tab[(int)(w->player.x)][(int)(w->player.y - \
					w->dir.y * w->player.mv_speed)])
			w->player.y -= w->dir.y * w->player.mv_speed;
	}
	if (in->keys[SDL_SCANCODE_RIGHT])
	{
		ft_rotation2d(&w->dir.x, &w->dir.y, -w->player.rot_speed);
		ft_rotation2d(&w->cam_plane.x, &w->cam_plane.y, -w->player.rot_speed);
	}
	if (in->keys[SDL_SCANCODE_LEFT])
	{
		ft_rotation2d(&w->dir.x, &w->dir.y, w->player.rot_speed);
		ft_rotation2d(&w->cam_plane.x, &w->cam_plane.y, w->player.rot_speed);
	}
}

void		ft_wolf_quit(t_wolf *w)
{
	int		i;

	i = -1;
	while (++i < 8)
	{
		free(w->tex2[i].pixels);
		w->tex2[i].pixels = NULL;
	}
	ft_sdl_quit(&w->ptr);
}
