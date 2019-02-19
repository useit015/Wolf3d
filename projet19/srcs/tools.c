/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 14:01:43 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/12 14:59:18 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_swap(void *const a, void *const b, size_t size)
{
	void	*temp;

	if ((temp = malloc(size)))
	{
		ft_memcpy(temp, a, size);
		ft_memcpy(a, b, size);
		ft_memcpy(b, temp, size);
		free(temp);
		temp = NULL;
	}
	else
	{
		write(1, "Error malloc\n", 13);
		exit(EXIT_FAILURE);
	}
}

void		ft_rotation2d(float *x, float *y, float angle)
{
	float prev_x;

	prev_x = *x;
	(*x) = (*x) * cosf(angle) - (*y) * sinf(angle);
	(*y) = prev_x * sinf(angle) + (*y) * cosf(angle);
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

void		ft_get_free_pos(t_map *m, float *x, float *y)
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
