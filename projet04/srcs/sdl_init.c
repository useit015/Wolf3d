/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:29:41 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/05 15:19:22 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/prototypes.h"


int		ft_sdl_init(t_ptr *ptr, int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		ft_sdl_error();
		return (-1);
	}
	if (!(ptr->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, \
			SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)))
	{
		ft_sdl_error();
		return (-1);
	}
		if (!(ptr->renderer = SDL_CreateRenderer(ptr->window, -1, SDL_RENDERER_PRESENTVSYNC\
			| SDL_RENDERER_ACCELERATED)))
	{
		return (-1);
	}
	if (!(ptr->texture = SDL_CreateTexture(ptr->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height)))
	{
		ft_sdl_error();
		return (-1);
	}
	return (0);
}

void	ft_clear_pixels(Uint32 *pixels)
{
	int		i;

	i = -1;
	while (++i < SCR_WIDTH * SCR_HEIGHT)
		pixels[i] = 0x000000;
}

int		ft_update_renderer(t_ptr ptr, Uint32 *pixels)
{
	(void)pixels;
	if (SDL_RenderClear(ptr.renderer))
	{
		ft_sdl_error();
		return (-1);
	}
	if (SDL_UpdateTexture(ptr.texture, NULL, pixels, SCR_WIDTH * sizeof(Uint32)))
	{
		ft_sdl_error();
		return (-1);
	}
	if (SDL_RenderCopy(ptr.renderer, ptr.texture, NULL, NULL))
	{
		ft_sdl_error();
		return (-1);
	}
	SDL_RenderPresent(ptr.renderer);
	return (0);
}

void	ft_sdl_quit(t_ptr *ptr)
{
	if (ptr->texture)
		SDL_DestroyTexture(ptr->texture), ptr->texture = NULL;
	if (ptr->window)
		SDL_DestroyWindow(ptr->window), ptr->window = NULL;
	if (ptr->renderer)
		SDL_DestroyRenderer(ptr->renderer), ptr->renderer = NULL;
	SDL_Quit();
}
