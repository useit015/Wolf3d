/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/08 21:36:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		main(int argc, char *argv[])
{
	t_wolf	w;
	t_input	in;
	int		status;

	status = EXIT_FAILURE;
	if (argc != 2)
	{
		ft_putendl("usage : ./test file_name");
		return (status);
	}
	if (ft_wolf_init(&w, argv[1]))
	{
		ft_wolf_quit(&w);
		return (status);
	}
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_draw(&w);
		ft_update_event(&in);
		ft_wolf_key(&w, &in);
	}
	status = EXIT_SUCCESS;
	ft_wolf_quit(&w);
	return (status);
}
