/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 21:35:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/03 23:58:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 1200
# define MAX_SIZE 500

# include <SDL2/SDL.h>
# include <sys/stat.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <libft.h>
# include <complex.h>

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
	double		mvspeed;
	double		rotspeed;
}					t_player;

typedef struct		s_wolf
{
	Uint32			*pixels;
	Uint32			color;
	t_ptr			ptr;
	t_map			map;
	t_player		player;
	t_vect2d		dir;
	t_vect2d		cam_plane;
	t_vect2d		ray_dir;
	t_vect2d		side_dist;
	t_vect2d		delta_dist;
	t_point			map_pos;
	t_point			step;
	int				w;
	int				h;
	int				hit;
	int				side;
	double			cam_x;
	double			per_wall_dist;
	t_point			p_start;
	t_point			p_dest;
	double			frame_time;
	Uint32			old_time;
	Uint32			curr_time;
}					t_wolf;


void		ft_draw(Uint32 *pixels);
void		ft_sdl_error(void);
void		ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color);
void		ft_clear_pixels(Uint32 *pixels);

int			ft_rgb_color(unsigned int r, unsigned int g, unsigned int b);
t_point		ft_point(int x, int y);
t_vect2d	ft_vector(double x, double y);
void		ft_get_free_pos(t_map *m, double *x, double *y);

int			ft_wolf_init(t_wolf *f, char *file);
void		ft_wolf_draw(t_wolf *f);
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

void		ft_fill_map(t_map *m, char *line, int y);
void		ft_read_file(t_map *m, char *file_name);
void		ft_error(void);
void		ft_sdl_quit(t_ptr *ptr);
#endif
