/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 19:10:31 by ebatchas          #+#    #+#             */
/*   Updated: 2018/12/16 17:20:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/complex.h"

double			ft_module(t_complex *c)
{
	return (sqrt(c->x * c->x + c->y * c->y));
}

t_complex		ft_add(t_complex a, t_complex b)
{
	t_complex	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_complex		ft_mult(t_complex *a, t_complex *b)
{
	t_complex	c;

	c.x = a->x * b->x - a->y * b->y;
	c.y = a->x * b->y + a->y * b->x;
	return (c);
}


t_complex		ft_sub(t_complex *a, t_complex *b)
{
	t_complex	c;

	c.x = a->x - b->x;
	c.y = a->y - b->y;
	return (c);
}

t_complex		ft_div(t_complex *a, t_complex *b)
{
	t_complex	c;

	c.x = (a->x * b->x + a->y * b->y) / (b->x * b->x + b->y * b->y);
	c.y = (a->y * b->x - a->x * b->y) / (b->x * b->x + b->y * b->y);
	return (c);
}

