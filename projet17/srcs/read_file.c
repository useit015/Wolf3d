/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 21:45:47 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/09 14:53:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		ft_error(void)
{
	ft_putendl("Error");
	exit(EXIT_FAILURE);
}

void		ft_fill_map(t_map *m, char *line, int y)
{
	char	**tab;
	int		x;

	tab = ft_strsplit(line, ' ');
	x = -1;
	while (tab[++x])
	{
		m->tab[y][x] = ft_atoi(tab[x]);
		if (m->tab[y][x] < 0 || m->tab[y][x] > 8)
			ft_error();
		if ((y == 0 || x == 0 || x == m->w - 1) && m->tab[y][x] == 0)
			ft_error();
	}
	if (!m->w)
		m->w = x;
	if (m->w && x != m->w)
		ft_error();
}

void		ft_read_file(t_map *m, char *file_name)
{
	int		fd;
	char	*line;
	int		y;

	fd = open(file_name, O_RDONLY);
	y = 0;
	m->w = 0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		ft_fill_map(m, line, y++);
		while (ft_get_next_line(fd, &line))
			ft_fill_map(m, line, y++);
		m->h = y;
		if (!m->w || !m->h)
			ft_error();
		y = -1;
		while (m->tab[m->h - 1][++y] > 0)
			;
		if (m->w != y)
			ft_error();
	}
	else
		ft_error();
}
