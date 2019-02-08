/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:35:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/27 10:28:18 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 800
# define MAX_SIZE 500
# define NB_SPRITES 19
# define NB_THREADS 6
# define NB_TEXT 12
# define NB_TILES 12
# define TILE_WIDTH 64
# define TILE_HEIGHT 64

# include <SDL2/SDL.h>
# include <sys/stat.h>
# include <math.h>
# include <pthread.h>
# include <fcntl.h>
# include <libft.h>
# include <complex.h>

# define ft_abs(n) (((n) < (0)) ? (-n) : (n))

typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef	struct		s_vect2d
{
	double	x;
	double	y;
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
	int		mousex;
	int		mousey;
	int		xwheel;
	int		ywheel;
	int		mousexrel;
	int		mouseyrel;
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

typedef	struct		t_map
{
	int				tab[MAX_SIZE][MAX_SIZE];
	int				w;
	int				h;
}					t_map;

typedef struct		s_player
{
	double		x;
	double		y;
	double		mv_speed;
	double		rot_speed;
}					t_player;

typedef struct		s_sprite
{
	double		x;
	double		y;
	int			texture;
}					t_sprite;

typedef struct		s_wolf
{
	Uint32			*pixels;
	t_img			tex1[NB_TILES];
	t_img			tex2[NB_TILES];
	t_map			map;
	t_ptr			ptr;
	t_player		player;
	t_sprite		sprite[NB_SPRITES];
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
	double			wall_x;
	double			weight;
	double			per_wall_dist;
	double			cam_x;
	double			frame_time;
	double			z_buffer[SCR_WIDTH];
	double			sprite_dist[NB_SPRITES];
	double			inv_det;
	int				x;
	int				d;
	int				help;
	int				type;
	Uint32			color;
	Uint32			xorcolor;
	Uint32			ycolor;
	Uint32			xycolor;
	Uint32			curr_time;
	Uint32			old_time;
	int				hit;
	int				side;
	int				line_height;
	int				tile_num;
	int				w;
	int				h;
	int				sprite_screen;
	int				sprite_order[NB_SPRITES];
	int				tex_x;
	int				tex_y;
}					t_wolf;

typedef struct		s_arg
{
	int		k;
	t_wolf	w;
}					t_arg;

void		ft_swap(void *const a, void *const b, size_t size);
void		ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel);
Uint32 		ft_get_pixels(SDL_Surface *s, int x, int y);
SDL_Texture	*ft_load_image(SDL_Renderer *renderer, char *file_name);
Uint32		*ft_load_pixels(SDL_Renderer *renderer, char *file_name);

void		ft_sdl_error(void);
void		ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color);
void		ft_clear_pixels(Uint32 *pixels);

int			ft_rgb_color(unsigned int r, unsigned int g, unsigned int b);
t_point		ft_point(int x, int y);
t_vect2d	ft_vector(double x, double y);
t_sprite	ft_sprite(double x, double y, int text);
void		ft_get_free_pos(t_map *m, double *x, double *y);

void		ft_draw(t_wolf *w);

void		ft_init_variables1(t_wolf *w);
void		ft_init_variables2(t_wolf *w);
void		ft_wolf_load1(t_wolf *w);
void		ft_wolf_load2(t_wolf *w);
int			ft_wolf_init(t_wolf *f, char *file);
void		ft_wolf_dda_helper(t_wolf *w);
void		ft_wolf_dda(t_wolf *w);
void		ft_wolf_end(t_wolf *w);
void		ft_wolf_cell_floorh(t_wolf *w);
void		ft_wolf_cell_floor(t_wolf *w);
void		ft_draw_map(t_wolf *w);
void		*ft_wolf_draw(void *argv);
void		ft_wolf_type1(t_wolf *w);
void		ft_wolf_type2(t_wolf *w);
void		ft_wolf_key(t_wolf *f, t_input *in);
void		ft_wolf_quit(t_wolf *f);

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_line(Uint32 *pixels, t_point p1, t_point p2, Uint32 color);
void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int radius , Uint32 color);
void		ft_sdl_draw_disc(Uint32 *pixels, t_point co, int radius, Uint32 color);
void		ft_sdl_draw_rect(Uint32 *pixels, t_rect rect, Uint32 color);

void		ft_update_event(t_input *in);
void		ft_handle_input(t_input *in, int *opt, double *delta);
int			ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
int			ft_update_renderer(t_ptr ptr, Uint32 *pixel);

void		ft_rotation2d(double *x, double *y, double angle);
void		ft_get_wolfcolor(t_map *m, int x, int y, Uint32 *color);

void		ft_wolf_sprite(t_wolf *w);
void		ft_sprite_sort(int *order, double *dist, int n);

void		ft_fill_map(t_map *m, char *line, int y);
void		ft_read_file(t_map *m, char *file_name);
void		ft_error(void);
void		ft_sdl_quit(t_ptr *ptr);
#endif
