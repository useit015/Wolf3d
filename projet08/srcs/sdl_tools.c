/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 19:05:16 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/08 16:59:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void	ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel)
{
	int		bpp;
	Uint8	*p;

	bpp = s->format->BytesPerPixel;
	p = (Uint8 *)s->pixels + y * s->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 2)
		*(Uint32 *)p = pixel;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel & 0xFF);
		}
		else
		{
			p[0] = pixel & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel >> 16) & 0xFF;
		}
	}
	else
		*(Uint32 *)p = pixel;
}

Uint32 	ft_get_pixels(SDL_Surface *s, int x, int y)
{

	int		bpp;
	Uint8	*p;

	bpp = s->format->BytesPerPixel;
	p = (Uint8 *)s->pixels + y * s->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	if (bpp == 2)
		return (*(Uint16 *)p);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}


Uint32	*ft_load_pixels(SDL_Renderer *renderer, char *file_name)
{
	SDL_Surface		*s;
	int				x;
	int				y;
	Uint32			*pixels;

	(void)renderer;
	s = SDL_LoadBMP(file_name);
	if (!s)
		ft_sdl_error();
	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 0, 0, 0));
	pixels = (Uint32 *)malloc(sizeof(Uint32) * (TILE_WIDTH * TILE_HEIGHT));
	SDL_LockSurface(s);
	y = -1;
	while ((++y < TILE_HEIGHT) && (x = -1))
		while (++x < TILE_WIDTH)
			pixels[y * TILE_WIDTH + x] = ft_get_pixels(s, x, y);
	SDL_UnlockSurface(s->pixels);
	SDL_FreeSurface(s);
	s = NULL;
	return (pixels);
}

SDL_Texture	*ft_load_image(SDL_Renderer *renderer, char *file_name)
{
	SDL_Surface		*s;
	SDL_Texture		*t;

	s = SDL_LoadBMP(file_name);
	if (!s)
		ft_sdl_error();
	SDL_SetColorKey(s, SDL_TRUE, SDL_MapRGB(s->format, 0, 0, 0));
	t = SDL_CreateTextureFromSurface(renderer, s);
	if (!t)
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
	return (t);
}
