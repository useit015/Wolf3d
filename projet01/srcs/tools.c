/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:14:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/04 03:38:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

void		ft_rotation2d(double *x, double *y, double angle)
{
	double prev_x;

	prev_x = *x;
	(*x) = (*x) * cos(angle) - (*y) * sin(angle);
	(*y) = prev_x * sin(angle) + (*y) * cos(angle);
}

void		ft_get_wolfcolor(t_map *m, int x, int y, Uint32 *color)
{
	if (m->tab[x][y] == 1)
		*color = 0xFF0000;
	else if (m->tab[x][y] == 2)
		*color = 0x00FF00;
	else if (m->tab[x][y] == 3)
		*color = 0x0000FF;
	else if (m->tab[x][y] == 4)
		*color = 0xFFFFFF;
	else
		*color = 0xFF00FF;
}
