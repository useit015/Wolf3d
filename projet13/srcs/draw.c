/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 17:07:26 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		*ft_wolf_draw(void *argv)
{
	t_arg	*arg;
	int		k;

	arg = (t_arg *)argv;
	arg->w.x = arg->k * arg->w.w / NB_THREADS - 1;
	k = (arg->k + 1) * arg->w.w / NB_THREADS;
	while (++arg->w.x < k)
	{
		ft_wolf_dda_helper(&arg->w);
		ft_wolf_dda(&arg->w);
		ft_wolf_end(&arg->w);
	}
	pthread_exit(NULL);
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
	if (in->resized)
	{
		SDL_GetWindowSize(w->ptr.window, &w->w, &w->h);
		free(w->pixels);
		w->pixels = ft_create_pixels(w->w, w->h);
		in->resized = 0;
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

void		ft_draw(t_wolf *w)
{
	int				k;
	t_arg			arg[NB_THREADS];
	pthread_t		t[NB_THREADS];
	pthread_attr_t	attr[NB_THREADS];

	k = -1;
	ft_clear_pixels(w->pixels);
	SDL_RenderClear(w->ptr.renderer);
	while (++k < NB_THREADS)
	{
		arg[k].k = k;
		arg[k].w = *w;
		pthread_attr_init(&attr[k]);
		pthread_create(&t[k], &attr[k], &ft_wolf_draw, (void *)&arg[k]);
	}
	while (--k > -1)
		pthread_join(t[k], NULL);
	if (w->help)
		ft_draw_map(w);
	w->old_time = w->curr_time;
	w->curr_time = SDL_GetTicks();
	w->frame_time = (w->curr_time - w->old_time) / 1000.0;
	ft_update_renderer(w->ptr, w->pixels);
	w->player.mv_speed = (w->frame_time) * 5.0;
	w->player.rot_speed = (w->frame_time) * 3.0;
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
