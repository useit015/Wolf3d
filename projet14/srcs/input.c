/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:11:44 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/13 19:01:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_update_event(t_input *in)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			in->quit = SDL_TRUE;
		if (event.type == SDL_KEYDOWN)
			in->keys[event.key.keysym.scancode] = SDL_TRUE;
		if (event.type == SDL_KEYUP)
			in->keys[event.key.keysym.scancode] = SDL_FALSE;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			in->mouse[event.button.button] = SDL_TRUE;
		if (event.type == SDL_MOUSEBUTTONUP)
			in->mouse[event.button.button] = SDL_FALSE;
		if (event.type == SDL_WINDOWEVENT)
			in->resized = (event.window.event == SDL_WINDOWEVENT_RESIZED);
	}
}
