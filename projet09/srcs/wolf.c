/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 17:42:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/31 11:08:20 by ebatchas         ###   ########.fr       */
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

void	ft_init_variables1(t_wolf *w)
{
	w->player.mv_speed = 0.0;
	w->player.rot_speed = 0.0;
	w->dir = ft_vector(-1.0, 0.0);
	w->cam_plane = ft_vector(0, 0.66);
	w->ray_dir = ft_vector(0.0, 0.0);
	w->delta_dist = ft_vector(0.0, .0);
	w->side_dist = ft_vector(0.0, 0.0);
	w->sprite_pos = ft_vector(0.0, 0.0);
	w->map_pos = ft_point(12, 12);
	w->step = ft_point(0, 0);
	w->tile_p = ft_point(0, 0);
	w->sprite_pos = ft_vector(0.0, .0);
	w->sprite_trans = ft_vector(0.0, .0);
	w->d = 0;
	w->h = 0;
	w->hit = 0;
	w->help = 0;
	w->side = 0;
	w->type = 1;
	w->line_height = 0;
	w->frame_time = 0.0;
	w->tile_num = 0;
	w->ps = ft_point(0, 0);
	w->pd = ft_point(0, 0);
	w->w = SCR_WIDTH;
	w->h = SCR_HEIGHT;
	w->scr = ft_point(SCR_WIDTH, SCR_HEIGHT);
	w->weight = 0;
	w->per_wall_dist = .0;
}

void	ft_init_variables2(t_wolf *w)
{
	w->tile_floor = ft_point(0, 0);
	w->sp_start = ft_point(0, 0);
	w->sp_end = ft_point(0, 0);
	w->sprite_size = ft_point(0, 0);
	w->xorcolor = 0xFFF0FF;
	w->ycolor = 0xFDFFDD;
	w->wall_x = 0.0;
	w->tex_x = 0;
	w->inv_det = 0.0;
	w->tex_y = 0;
	w->sprite_screen = 0;
	w->sprite[0] = ft_sprite(20.5, 11.5, 10);
	w->sprite[1] = ft_sprite(18.5, 4.5, 10);
	w->sprite[2] = ft_sprite(10.0, 4.5, 10);
	w->sprite[3] = ft_sprite(10.0, 12.5, 10);
	w->sprite[4] = ft_sprite(3.5, 6.5, 10);
	w->sprite[5] = ft_sprite(3.5, 20.5, 10);
	w->sprite[6] = ft_sprite(3.5, 14.5,10);
	w->sprite[7] = ft_sprite(14.5,20.5,10);
	w->sprite[8] = ft_sprite(18.5, 10.5, 9);
	w->sprite[9] = ft_sprite(18.5, 11.5, 9);
	w->sprite[10] = ft_sprite(18.5, 12.5, 9);
	w->sprite[11] = ft_sprite(1.5, 1.5, 8);
	w->sprite[12] = ft_sprite(15.5, 1.5, 8);
	w->sprite[13] = ft_sprite(16.0, 1.8, 8);
	w->sprite[14] = ft_sprite(16.2, 1.2, 8);
	w->sprite[15] = ft_sprite(3.5,  2.5, 8);
	w->sprite[16] = ft_sprite(9.5, 15.5, 8);
	w->sprite[17] = ft_sprite(10.0, 15.1,8);
	w->sprite[18] = ft_sprite(10.5, 15.8,8);
}

void	ft_wolf_load1(t_wolf *w)
{
	w->tex2[0].pixels = ft_load_pixels(w->ptr.renderer, "images/eagle.bmp");
	w->tex2[1].pixels = ft_load_pixels(w->ptr.renderer, "images/redbrick.bmp");
	w->tex2[2].pixels = ft_load_pixels(w->ptr.renderer, "images/purplestone.bmp");
	w->tex2[3].pixels = ft_load_pixels(w->ptr.renderer, "images/greystone.bmp");
	w->tex2[4].pixels = ft_load_pixels(w->ptr.renderer, "images/bluestone.bmp");
	w->tex2[5].pixels = ft_load_pixels(w->ptr.renderer, "images/mossy.bmp");
	w->tex2[6].pixels = ft_load_pixels(w->ptr.renderer, "images/wood.bmp");
	w->tex2[7].pixels = ft_load_pixels(w->ptr.renderer, "images/colorstone.bmp");

	w->tex2[8].pixels = ft_load_pixels(w->ptr.renderer, "images/barrel.bmp");
	w->tex2[9].pixels = ft_load_pixels(w->ptr.renderer, "images/pillar.bmp");
	w->tex2[10].pixels = ft_load_pixels(w->ptr.renderer, "images/greenlight.bmp");
}

void	ft_wolf_load2(t_wolf *w)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 8)
		w->tex1[i].pixels = (Uint32 *)malloc(sizeof(Uint32) * TILE_WIDTH * TILE_HEIGHT);
	i = -1;
	while ((++i < TILE_HEIGHT) && (j = -1))
		while (++j < TILE_WIDTH)
		{
			w->xorcolor = (i * 256 / TILE_WIDTH) ^ (j * 256 / TILE_HEIGHT);
			w->ycolor = j * 256 / TILE_WIDTH;
			w->xycolor = j * 128 / TILE_HEIGHT + i * 128 / TILE_WIDTH;
			w->tex1[0].pixels[i * TILE_WIDTH + j]  = 65536 * 254 * (i != j && i != TILE_WIDTH - j);
			w->tex1[1].pixels[i * TILE_WIDTH + j] = w->xycolor + 256 * w->xycolor + 65536 * w->xycolor;
			w->tex1[2].pixels[i * TILE_WIDTH + j]  = 256 * w->xycolor + 65536 * w->xycolor;
			w->tex1[3].pixels[i * TILE_WIDTH + j]  = w->xorcolor + 256 * w->xorcolor + 65536 * w->xorcolor;
			w->tex1[4].pixels[i * TILE_WIDTH + j]  = 256 * w->xorcolor;
			w->tex1[5].pixels[i * TILE_WIDTH + j]  = 65536 * 192 * (i % 16 && j % 16);
			w->tex1[6].pixels[i * TILE_WIDTH + j]  = 65536 * w->ycolor;
			w->tex1[7].pixels[i * TILE_WIDTH + j]  = 128 + 256 * 128 + 65536 * 128;
		}
}

int		ft_wolf_init(t_wolf *w, char *file)
{
	ft_init_variables1(w);
	ft_init_variables2(w);
	ft_read_file(&w->map, file);
	ft_wolf_load2(w);
	ft_get_free_pos(&w->map, &w->player.x, &w->player.y);
	ft_sdl_init(&w->ptr, SCR_WIDTH, SCR_HEIGHT, "42 SDL");
	w->pixels = (Uint32 *)malloc(sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_memset(w->pixels, 0, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_wolf_load1(w);
	/*w->player.x = 12.0;
	  w->player.y = 11.0;*/
	return (0);
}

void	*ft_wolf_draw(void *argv)
{
	t_arg	*arg;
	int		k;


	arg = (t_arg *)argv;
	arg->w.x = arg->k * SCR_WIDTH / NB_THREADS - 1;
	k = (arg->k + 1) * SCR_WIDTH / NB_THREADS;
	while (++arg->w.x < k)
	{
		ft_wolf_dda_helper(&arg->w);
		ft_wolf_dda(&arg->w);
		ft_wolf_end(&arg->w);
	}
	pthread_exit(NULL);
}

void	ft_wolf_keyh(t_wolf *w, t_input *in)
{
	if (in->keys[SDL_SCANCODE_ESCAPE])
		in->quit = SDL_TRUE;
	if (in->keys[SDL_SCANCODE_T])
		w->type = ++w->type % 3;
	if (in->keys[SDL_SCANCODE_H])
		w->help = ++w->help % 2;
}
void	ft_wolf_key(t_wolf *w, t_input *in)
{
	ft_wolf_keyh(w, in);
	if (in->keys[SDL_SCANCODE_UP])
	{
		if (!w->map.tab[(int)(w->player.x + w->dir.x * w->player.mv_speed)][(int)(w->player.y)])
			w->player.x += w->dir.x * w->player.mv_speed;
		if (!w->map.tab[(int)(w->player.x)][(int)(w->player.y + w->dir.y * w->player.mv_speed)])
			w->player.y += w->dir.y * w->player.mv_speed;
	}
	if (in->keys[SDL_SCANCODE_DOWN])
	{
		if (!w->map.tab[(int)(w->player.x - w->dir.x * w->player.mv_speed)][(int)(w->player.y)])
			w->player.x -= w->dir.x * w->player.mv_speed;
		if (!w->map.tab[(int)(w->player.x)][(int)(w->player.y - w->dir.y * w->player.mv_speed)])
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

void	ft_wolf_quit(t_wolf *w)
{
	int		i;

	i = -1;
	while (++i < 8)
		free(w->tex2[i].pixels), w->tex2[i].pixels = NULL;
	ft_sdl_quit(&w->ptr);
}
