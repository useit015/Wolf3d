/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/19 07:57:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

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
	if (in->keys[SDL_SCANCODE_S])
		w->s = ++w->s % 2;
	if (in->resized)
	{
		SDL_GetWindowSize(w->ptr.window, &w->w, &w->h);
		free(w->pixels);
		w->pixels = ft_create_pixels(w->w, w->h);
		in->resized = 0;
	}
	if (in->keys[SDL_SCANCODE_SPACE])
	{
		t_sprite	*new;
		t_vect2d	v = { w->dir.x * 0.5f,  0.5 * w->dir.y};
		if (w->nb_sprites < 256 && (new = ft_create_sprites(ft_vector(w->player.x, w->player.y), v, 8)))
		{
			ft_push_back_sprites(&w->sprites, new);
			w->nb_sprites++;
			printf("\n NB == %d|", w->nb_sprites);
		}
		/*if ((new = ft_create_sprites(ft_vector(w->w / 2.0, w->h - 10.0), v, 8)))
		{
			ft_push_back_sprites(&w->sprites, new);
			w->nb_sprites++;
		}*/
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

void		ft_wolf_draw(t_wolf *w)
{
	w->x = -1;
	ft_clear_pixels(w->pixels);
	SDL_RenderClear(w->ptr.renderer);
	while (++w->x < w->w)
	{
		ft_wolf_dda_helper(w);
		ft_wolf_dda(w);
		ft_wolf_end(w);
	}
	if (w->s)
		ft_wolf_sprite(w);
	if (w->help)
		ft_draw_map(w);
	w->old_time = w->curr_time;
	w->curr_time = SDL_GetTicks();
	w->frame_time = (w->curr_time - w->old_time) / 800.0;
	ft_update_renderer(w->ptr, w->pixels);
	w->player.mv_speed = (w->frame_time) * 5.0;
	w->player.rot_speed = (w->frame_time) * 3.0;
	ft_clear_sprites(&w->sprites);
	w->nb_sprites =  ft_length_sprites(w->sprites);
}

void		ft_wolf_quit(t_wolf *w)
{
	int		i;

	i = -1;
	while (++i < 13)
	{
		free(w->tex2[i].pixels);
		w->tex2[i].pixels = NULL;
	}
	free(w->sprite_dist);
	free(w->sprite_order);
	ft_free_sprites(&w->sprites);
	ft_sdl_quit(&w->ptr);
}
