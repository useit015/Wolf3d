/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:00:35 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 19:21:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define T_W 64
# define T_H 64
# define N1 16646144
# define N2 65536

# include "structs.h"
# include "libft.h"
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>

t_sprite	*ft_create_sprites(t_vect2d pos, t_vect2d v, int texture);
void		ft_push_back_sprites(t_sprite **s, t_sprite *nw);
void		ft_pop_front_sprites(t_sprite **s);
void		ft_pop_back_sprites(t_sprite **s);
void		ft_free_sprites(t_sprite **s);
int			ft_length_sprites(t_sprite *s);
void		ft_clear_sprites(t_sprite **s, int indice);

void		ft_swap(void *const a, void *const b, size_t size);
void		ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel);
Uint32		ft_get_pixels(SDL_Surface *s, int x, int y);
SDL_Texture	*ft_load_image(SDL_Renderer *renderer, char *file_name);
Uint32		*ft_load_pixels(SDL_Renderer *renderer, char *file_name);
Uint32		*ft_create_pixels(int w, int h);

int			ft_sdl_error(void);
void		ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color);
void		ft_clear_pixels(Uint32 *pixels);

int			ft_rgb_color(unsigned int r, unsigned int g, unsigned int b);
t_point		ft_point(int x, int y);
t_vect2d	ft_vector(float x, float y);
t_sprite	ft_sprite(float x, float y, int text);
void		ft_get_free_pos(t_map *m, float *x, float *y);

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
void		ft_draw(t_wolf *w);
void		ft_wolf_draw(t_wolf *w);
void		ft_wolf_type1(t_wolf *w);
void		ft_wolf_type2(t_wolf *w);
void		ft_wolf_key(t_wolf *f, t_input *in);
void		ft_wolf_quit(t_wolf *f);

void		ft_sdl_draw_octant1(Uint32 *pixels, t_point p, t_point q, Uint32 c);
void		ft_sdl_draw_octant2(Uint32 *pixels, t_point p, t_point q, Uint32 c);
void		ft_sdl_draw_line(Uint32 *pixels, t_point p1, t_point p2, Uint32 c);
void		ft_sdl_draw_circle(Uint32 *pixels, t_point co, int rad, Uint32 c);
void		ft_sdl_draw_disc(Uint32 *pixels, t_point co, int rad, Uint32 col);
void		ft_sdl_draw_rect(Uint32 *pixels, t_rect rect, Uint32 color);

void		ft_update_event(t_input *in);
void		ft_handle_input(t_input *in, int *opt, float *delta);
int			ft_sdl_init(t_ptr *ptr, int width, int height, const char *title);
int			ft_update_renderer(t_ptr ptr, Uint32 *pixel);

void		ft_rotation2d(float *x, float *y, float angle);
void		ft_get_wolfcolor(t_map *m, int x, int y, Uint32 *color);

void		ft_wolf_sprite(t_wolf *w);
void		ft_sprite_sort(int *order, float *dist, int n);

void		ft_fill_map(t_map *m, char *line, int y);
void		ft_read_file(t_map *m, char *file_name);
void		ft_error(void);
void		ft_sdl_quit(t_ptr *ptr);
#endif
