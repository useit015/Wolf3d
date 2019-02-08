/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:42:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/05 15:18:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void	ft_setrgb_color(SDL_Color *col, Uint32 color)
{
	col->b = color % 256;
	col->g = (color / 256) % 256;
	col->r = (color / (256 * 256));
	col->a = 255;
}

void	ft_init_variables(t_wolf *f)
{
	f->player.x = 12.0;
	f->player.y = 12.0;
	f->player.rotspeed = 0.0;
	f->player.mvspeed = 0.0;
	f->color = 0;
	f->dir = ft_vector(-1.0, .0);
	f->cam_plane = ft_vector(0.0, 0.99);
	f->ray_dir = ft_vector(0.0, .0);
	f->side_dist = ft_vector(0.0, .0);
	f->delta_dist = ft_vector(0.0, 0.0);
	f->map_pos = ft_point(12, 12);
	f->step = ft_point(-1, 1);
	f->hit = 0;
	f->side = 0;
	f->cam_x = .0;
	f->per_wall_dist = .0;
	f->p_start = ft_point(0, 0);
	f->p_dest = ft_point(0, 0);
	f->frame_time = 0.0;
	f->curr_time = 0;
	f->old_time = 0;
	f->w = SCR_WIDTH;
	f->h = SCR_HEIGHT;
}

int		ft_wolf_init(t_wolf *f, char *file)
{

	ft_init_variables(f);
	ft_read_file(&f->map, file);
	ft_sdl_init(&f->ptr, SCR_WIDTH, SCR_HEIGHT, file);
	f->pixels = (Uint32 *)malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_memset(f->pixels, 0x0, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	return (0);
}

void	ft_wolf_draw(t_wolf *f)
{
	int		x;
	int		line_height;
	
	x = -1;
	SDL_RenderClear(f->ptr.renderer);
	while (++x < f->w)
	{
		f->cam_x = 2 * x / (double) f->w - 1;
		f->ray_dir.x = f->dir.x + f->cam_plane.x * f->cam_x;
	   	f->ray_dir.y = f->dir.y + f->cam_plane.y * f->cam_x;
		f->delta_dist.x = fabs(1 / f->ray_dir.x);
		f->delta_dist.y = fabs(1 / f->ray_dir.y);
		f->hit = 0;
		f->map_pos.x = (int)f->player.x;
		f->map_pos.y = (int)f->player.y;
		if (f->ray_dir.x  < 0)
		{
			f->step.x = -1;
			f->side_dist.x = (f->player.x - f->map_pos.x) * f->delta_dist.x;
		}
		else
		{
			f->step.x = 1;
			f->side_dist.x = (f->map_pos.x + 1.0 - f->player.x) * f->delta_dist.x;
		}
		if (f->ray_dir.y < 0)
		{
			f->step.y = -1;
			f->side_dist.y = (f->player.y - f->map_pos.y) * f->delta_dist.y;
		}
		else
		{
			f->step.y = 1;
			f->side_dist.y = (f->map_pos.y + 1.0 - f->player.y) * f->delta_dist.y;
		}
		 //DDA
		while (!f->hit)
		{
			if (f->side_dist.x < f->side_dist.y)
			{
				f->side_dist.x += f->delta_dist.x;
				f->map_pos.x += f->step.x;
				f->side = 0;
			}
			else
			{
				f->side_dist.y += f->delta_dist.y;
				f->map_pos.y += f->step.y;
				f->side = 1;
			}
				if (f->map.tab[f->map_pos.x][f->map_pos.y] > 0)
				f->hit = 1;
		}
		if (!f->side)
			f->per_wall_dist = (f->map_pos.x - f->player.x + (1 - f->step.x) / 2) / f->ray_dir.x;
		else
			f->per_wall_dist = (f->map_pos.y - f->player.y + (1 - f->step.y) / 2) / f->ray_dir.y;
		f->p_start.x = x;
		f->p_dest.x = x;
		line_height = (int) (f->h / f->per_wall_dist);
		f->p_start.y = -line_height / 2 + f->h / 2;
		if (f->p_start.y < 0)
			f->p_start.y = 0;
		f->p_dest.y = line_height / 2 + f->h / 2;
		if (f->p_dest.y >= f->h)
			f->p_dest.y = f->h - 1;
		ft_get_wolfcolor(&f->map, f->map_pos.x, f->map_pos.y, &f->color);
		if (f->side == 1)
			f->color /= 2;
		ft_sdl_draw_line(f->pixels, f->p_start, f->p_dest, f->color);
		/*SDL_Color col;
	   	ft_setrgb_color(&col, f->color);
		SDL_SetRenderDrawColor(f->ptr.renderer, col.r, col.g, col.b, col.a);
		SDL_RenderDrawLine(f->ptr.renderer, f->p_start.x, f->p_start.y, f->p_dest.x, f->p_dest.y);
		SDL_RenderPresent(f->ptr.renderer);*/
	}
	f->old_time = f->curr_time;
	f->curr_time = SDL_GetTicks();
	f->frame_time = (f->curr_time - f->old_time) / 1000.0;
	ft_update_renderer(f->ptr, f->pixels);
	f->player.mvspeed = f->frame_time * 5.0;
	f->player.rotspeed = f->frame_time * 3.0;
	SDL_Delay(1);
}

void	ft_wolf_key(t_wolf *f, t_input *in)
{
	if (in->keys[SDL_SCANCODE_UP])
	{
		if (!f->map.tab[(int)(f->player.x + f->dir.x * f->player.mvspeed)][(int)(f->player.y)])
			f->player.x += f->dir.x * f->player.mvspeed;
		if (!f->map.tab[(int)(f->player.x)][(int)(f->player.y + f->dir.y * f->player.mvspeed)])
			f->player.y += f->dir.y * f->player.mvspeed;
	}
	if (in->keys[SDL_SCANCODE_DOWN])
	{
		if (!f->map.tab[(int)(f->player.x - f->dir.x * f->player.mvspeed)][(int)(f->player.y)])
			f->player.x -= f->dir.x * f->player.mvspeed;
		if (!f->map.tab[(int)(f->player.x)][(int)(f->player.y - f->dir.y * f->player.mvspeed)])
			f->player.y -= f->dir.y * f->player.mvspeed;
	}
	if (in->keys[SDL_SCANCODE_RIGHT])
	{
		ft_rotation2d(&f->dir.x, &f->dir.y, -f->player.rotspeed);
		ft_rotation2d(&f->cam_plane.x, &f->cam_plane.y, -f->player.rotspeed);
	}
	if (in->keys[SDL_SCANCODE_LEFT])
	{
		ft_rotation2d(&f->dir.x, &f->dir.y, f->player.rotspeed);
		ft_rotation2d(&f->cam_plane.x, &f->cam_plane.y, f->player.rotspeed);
	}
}

void	ft_wolf_quit(t_wolf *f)
{
	free(f->pixels);
	f->pixels = NULL;
	ft_sdl_quit(&f->ptr);
}
