/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 10:14:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/06 19:06:51 by ebatchas         ###   ########.fr       */
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
	else if (m->tab[x][y] == 5)
		*color = 0xFF00FF;
	else if (m->tab[x][y] == 6)
		*color = 0xFFFF00;
	else if (m->tab[x][y] == 7)
		*color = 0x00FFFF;
	else
		*color = 0xFF00FF;
}

void	ft_get_free_pos(t_map *m, double *x, double *y)
{
	int		i;
	int		j;

	i = -1;
	while ((++i < m->h) && (j = -1))
	{
		while (++j < m->w)
			if (!m->tab[i][j])
			{
				*x = (1 + j) * 1.0;
				*y = (1 + i) * 1.0;
				ft_putnbr(i);
				ft_putnbr(j);
				return ;
			}
	}
	if (i == m->h && j == m->w)
		ft_error();
}
