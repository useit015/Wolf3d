/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 14:52:37 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

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
	k = -1;
	while (++k < NB_THREADS)
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
