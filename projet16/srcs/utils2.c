/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:29:16 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/09 13:44:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

t_point		ft_point(int x, int y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vect2d	ft_vector(double x, double y)
{
	t_vect2d	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_sprite	ft_sprite(double x, double y, int tex)
{
	t_sprite	p;

	p.x = x;
	p.y = y;
	p.texture = tex;
	return (p);
}
