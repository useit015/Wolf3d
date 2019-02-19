/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:37:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/19 06:22:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structs.h"

t_sprite	*ft_create_sprites(t_vect2d pos, t_vect2d v, int texture)
{
	t_sprite	*new;

	if ((new = (t_sprite *)malloc(sizeof(*new))))
	{
		new->x = pos.x + v.x;
		new->y = pos.y + v.y;
		new->vx = v.x;
		new->vy = v.y;
		new->remove = 0;
		new->texture = texture;
		new->next = NULL;
	}
	return (new);
}

void		ft_push_back_sprites(t_sprite **s, t_sprite *new)
{
	t_sprite *p;

	if (!s || !new)
		return ;
	else if (!*s)
		*s = new;
	else
	{
		p = *s;
		while (p->next)
			p = p->next;
		if (p)
			p->next = new;
	}
}

void		ft_pop_front_sprites(t_sprite **s)
{
	t_sprite	*p;

	p = *s;
	if (p)
	{
		*s = (*s)->next;
		free(p);
		if (!*s)
			s = NULL;
	}
}

void		ft_pop_back_sprites(t_sprite **s)
{
	t_sprite	*p;
	t_sprite	*q;

	p = *s;
	while (p->next)
	{
		q = p;
		p = p->next;
	}
	if (p)
	{
		q->next = NULL;
		free(p);
	}
	if (!*s)
		s = NULL;
}

void		ft_free_sprites(t_sprite **s)
{
	t_sprite	*p;

	p = *s;
	while (p)
	{
		*s = (*s)->next;
		free(p);
		p = *s;
	}
	s = NULL;
}

t_sprite	*ft_sprites(t_sprite *s, int indice)
{
	while (s && (--indice >= 0))
		s = s->next;
	return (s);
}

void		ft_clear_sprites(t_sprite **s)
{
	t_sprite	*p;
	t_sprite	*q;

	p = *s;
	if (p)
	{
		while (p && !p->remove)
		{
			q = p;
			p = p->next;
		}
		if (p->remove)
		{
			if (q)
			{
				q->next = p->next;
				free(p);
			}
			if (!*s)
				s = NULL;
		}
	}
}

void		ft_print_sprites(t_sprite *s)
{
	for (int i = 0; s; i++)
	{
		printf("SPRITE : %d x : %.2f y : %.2f removable ? : %d\n", i, s->x, s->y, s->remove);
		s = s->next;
	}
}

int			ft_length_sprites(t_sprite *s)
{
	if (!s)
		return (0);
	return (1 + ft_length_sprites(s->next));
}
