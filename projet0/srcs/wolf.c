/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:42:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 21:32:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

int		ft_wolf_init(t_wolf *f, char *file)
{

	ft_read_file(&f->map, file);
	f->player.x = 8.0;
	f->player.y = 8.0;
	f->player.angle = 0.0;
	f->p_ray.x = 0.0;
	f->p_ray.y = 0.0;
	f->fov = 3.14159 / 4.0;
	f->r_angle = 0.0;
	f->dist = 0.0;
	f->dist_max = f->map.w * f->map.h * 1.0;
	ft_sdl_init(&f->ptr, SCR_WIDTH, SCR_HEIGHT, file);
	f->pixels = (Uint32 *)malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_memset(f->pixels, 0x0, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	return (0);
}

void	ft_wolf_draw(t_wolf *f)
{
	int		j;
	t_point	p;
	int		ceilling;
	int		floor;
	int		hit_wall;

	j = -1;
	while (++j < SCR_WIDTH)
	{
		f->r_angle = (f->player.angle - f->fov / 2.0) + ((double) j / (double)SCR_WIDTH * f->fov);
		f->dist = .0;
		f->p_ray = ft_vector(sin(f->r_angle), cos(f->r_angle));
		hit_wall = 0;
		while (!hit_wall && f->dist < f->dist_max)
		{
			f->dist += 0.1;
			p.x = (int) (f->player.x + f->p_ray.x * f->dist);
			p.y = (int) (f->player.y + f->p_ray.y * f->dist);
			if (p.x < 0 || p.x >= f->map.w || p.y < 0 || p.y >= f->map.h)
			{
				hit_wall = 1;
				f->dist = f->dist_max;
			}
			else
			{
				if (f->map.tab[p.y][p.x] == 1)
					hit_wall = 1;
			}
		}
		ceilling = (double) SCR_HEIGHT / 2.0 - SCR_HEIGHT / f->dist;
		floor = SCR_HEIGHT - ceilling;
		for (int y = 0; y < SCR_HEIGHT; y++)
		{
			if (y < ceilling)
				f->pixels[y * SCR_WIDTH + j] = 0xBADA55;
			else if (y >= ceilling && y <= floor)
				f->pixels[y * SCR_WIDTH + j] = 0xFFFF00;
			else
				f->pixels[y * SCR_WIDTH + j] = 0x000022;
		}
	}
	ft_update_renderer(f->ptr, f->pixels);
}

void	ft_wolf_quit(t_wolf *f)
{
	free(f->pixels);
	f->pixels = NULL;
	ft_sdl_quit(&f->ptr);
}
