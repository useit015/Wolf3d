/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:38:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 18:53:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "SDL2/SDL.h"
# define MAX_SIZE 500
# define SCR_WIDTH 800
# define SCR_HEIGHT 600
# define NB_SPRITES 19
# define NB_TEXT 14
# define NB_TILES 14

# define SET(n, min, max) ((n < min) ? (min) : (n > max) ? (max) : (n))

typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef	struct		s_vect2d
{
	float	x;
	float	y;
}					t_vect2d;

typedef	struct		s_rect
{
	int		x;
	int		y;
	int		w;
	int		h;
}					t_rect;

typedef struct		s_input
{
	int		quit;
	int		resized;
	int		mouse[6];
	int		keys[SDL_NUM_SCANCODES];
}					t_input;

typedef	struct		s_ptr
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
}					t_ptr;

typedef	struct		s_img
{
	Uint32			*pixels;
}					t_img;

typedef	struct		s_map
{
	int				tab[MAX_SIZE][MAX_SIZE];
	int				w;
	int				h;
}					t_map;

typedef struct		s_player
{
	float		x;
	float		y;
	float		mv_speed;
	float		rot_speed;
}					t_player;

typedef struct		s_sprite
{
	float				x;
	float				y;
	float				vx;
	float				vy;
	int					remove;
	int					texture;
	struct	s_sprite	*next;
}					t_sprite;

typedef struct		s_wolf
{
	Uint32			*pixels;
	t_img			tex1[NB_TILES];
	t_img			tex2[NB_TILES];
	t_map			map;
	t_ptr			ptr;
	t_player		player;
	t_sprite		*sprites;
	t_vect2d		dir;
	t_vect2d		cam_plane;
	t_vect2d		ray_dir;
	t_vect2d		delta_dist;
	t_vect2d		side_dist;
	t_vect2d		p_floor;
	t_vect2d		cur_floor;
	t_vect2d		sprite_pos;
	t_vect2d		sprite_trans;
	t_point			scr;
	t_point			ps;
	t_point			pd;
	t_point			tile_p;
	t_point			tile_floor;
	t_point			map_pos;
	t_point			step;
	t_point			sprite_size;
	t_point			sp_start;
	t_point			sp_end;
	float			wall_x;
	float			weight;
	float			per_wall_dist;
	float			cam_x;
	float			frame_time;
	float			z_buffer[SCR_WIDTH];
	float			*sprite_dist;
	int				nb_sprites;
	float			inv_det;
	int				x;
	int				d;
	int				s:2;
	int				help;
	int				type;
	Uint32			color;
	Uint32			c1;
	Uint32			c2;
	Uint32			c3;
	Uint32			curr_time;
	Uint32			old_time;
	int				hit;
	int				side;
	int				line_height;
	int				tile_num;
	int				w;
	int				h;
	int				temp;
	int				sprite_screen;
	int				*sprite_order;
	int				tex_x;
	int				tex_y;
}					t_wolf;

#endif
