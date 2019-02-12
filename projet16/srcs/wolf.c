/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:54:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 14:38:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

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
	w->wall_x = 0.0;
	w->tile_num = 0;
	w->ps = ft_point(0, 0);
	w->pd = ft_point(0, 0);
}

void	ft_init_variables2(t_wolf *w)
{
	w->inv_det = 0.0;
	w->tex_y = 0;
	w->temp = 0;
	w->s = 0;
	w->tex_x = 0;
	w->sprite_screen = 0;
	w->sprite[0] = ft_sprite(20.5, 11.5, 11);
	w->sprite[1] = ft_sprite(18.5, 4.5, 10);
	w->sprite[2] = ft_sprite(10.0, 4.5, 12);
	w->sprite[3] = ft_sprite(10.0, 12.5, 10);
	w->sprite[4] = ft_sprite(3.5, 6.5, 10);
	w->sprite[5] = ft_sprite(3.5, 20.5, 13);
	w->sprite[6] = ft_sprite(3.5, 14.5, 10);
	w->sprite[7] = ft_sprite(14.5, 20.5, 10);
	w->sprite[8] = ft_sprite(18.5, 10.5, 9);
	w->sprite[9] = ft_sprite(18.5, 11.5, 9);
	w->sprite[10] = ft_sprite(18.5, 12.5, 9);
	w->sprite[11] = ft_sprite(1.5, 1.5, 8);
	w->sprite[12] = ft_sprite(15.5, 1.5, 12);
	w->sprite[13] = ft_sprite(16.0, 1.8, 12);
	w->sprite[14] = ft_sprite(16.2, 1.2, 12);
	w->sprite[15] = ft_sprite(3.5, 2.5, 11);
	w->sprite[16] = ft_sprite(9.5, 15.5, 8);
	w->sprite[17] = ft_sprite(10.0, 15.1, 8);
	w->sprite[18] = ft_sprite(10.5, 15.8, 10);
}

void	ft_wolf_load1(t_wolf *w)
{
	w->w = SCR_WIDTH;
	w->h = SCR_HEIGHT;
	w->scr = ft_point(SCR_WIDTH, SCR_HEIGHT);
	w->weight = 0;
	w->per_wall_dist = .0;
	w->tile_floor = ft_point(0, 0);
	w->sp_start = ft_point(0, 0);
	w->sp_end = ft_point(0, 0);
	w->sprite_size = ft_point(0, 0);
	w->c1 = 0xFFF0FF;
	w->c2 = 0xFDFFDD;
	w->tex2[0].pixels = ft_load_pixels(w->ptr.renderer, "imgs/eagle.bmp");
	w->tex2[1].pixels = ft_load_pixels(w->ptr.renderer, "imgs/redbrick.bmp");
	w->tex2[2].pixels = ft_load_pixels(w->ptr.renderer, "imgs/purplestone.bmp");
	w->tex2[3].pixels = ft_load_pixels(w->ptr.renderer, "imgs/greystone.bmp");
	w->tex2[4].pixels = ft_load_pixels(w->ptr.renderer, "imgs/bluestone.bmp");
	w->tex2[5].pixels = ft_load_pixels(w->ptr.renderer, "imgs/mossy.bmp");
	w->tex2[6].pixels = ft_load_pixels(w->ptr.renderer, "imgs/wood.bmp");
	w->tex2[7].pixels = ft_load_pixels(w->ptr.renderer, "imgs/colorstone.bmp");
	w->tex2[8].pixels = ft_load_pixels(w->ptr.renderer, "imgs/barrel.bmp");
	w->tex2[9].pixels = ft_load_pixels(w->ptr.renderer, "imgs/pillar.bmp");
	w->tex2[10].pixels = ft_load_pixels(w->ptr.renderer, "imgs/greenlight.bmp");
	w->tex2[11].pixels = ft_load_pixels(w->ptr.renderer, "imgs/armor.bmp");
	w->tex2[12].pixels = ft_load_pixels(w->ptr.renderer, "imgs/plantgreen.bmp");
	w->tex2[13].pixels = ft_load_pixels(w->ptr.renderer, "imgs/chairs.bmp");
}

int		ft_wolf_init(t_wolf *w, char *file)
{
	ft_init_variables1(w);
	ft_init_variables2(w);
	ft_read_file(&w->map, file);
	ft_wolf_load2(w);
	w->tex1[8].pixels = ft_load_pixels(w->ptr.renderer, "imgs/sol.bmp");
	w->tex1[9].pixels = ft_load_pixels(w->ptr.renderer, "imgs/mur.bmp");
	w->tex1[10].pixels = ft_load_pixels(w->ptr.renderer, "imgs/plafond.bmp");
	ft_get_free_pos(&w->map, &w->player.x, &w->player.y);
	ft_sdl_init(&w->ptr, SCR_WIDTH, SCR_HEIGHT, "42 WOLF3D");
	w->pixels = ft_create_pixels(SCR_WIDTH, SCR_HEIGHT);
	ft_memset(w->pixels, 0, sizeof(Uint32) * SCR_WIDTH * SCR_HEIGHT);
	ft_wolf_load1(w);
	return (0);
}

void	ft_wolf_load2(t_wolf *w)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 8)
		w->tex1[i].pixels = ft_create_pixels(T_W, T_H);
	i = -1;
	while ((++i < T_H) && (j = -1))
	{
		while (++j < T_W)
		{
			w->c1 = (i * 256 / T_W) ^ (j * 256 / T_H);
			w->c2 = j * 256 / T_W;
			w->c3 = j * 128 / T_H + i * 128 / T_W;
			w->tex1[0].pixels[i * T_W + j] = N1 * (i != j && i != T_W - j);
			w->tex1[1].pixels[i * T_W + j] = w->c3 + 256 * w->c3 + N2 * w->c3;
			w->tex1[2].pixels[i * T_W + j] = 256 * w->c3 + N2 * w->c3;
			w->tex1[3].pixels[i * T_W + j] = w->c1 + 256 * w->c1 + N2 * w->c1;
			w->tex1[4].pixels[i * T_W + j] = 256 * w->c1;
			w->tex1[5].pixels[i * T_W + j] = N2 * 192 * (i % 16 && j % 16);
			w->tex1[6].pixels[i * T_W + j] = N2 * w->c2;
			w->tex1[7].pixels[i * T_W + j] = 128 + 256 * 128 + N2 * 128;
		}
	}
}
