/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/01/27 09:21:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

int		main(int argc, char *argv[])
{
	t_wolf	w;
	t_input	in;
	int		status;

	status = EXIT_FAILURE;
	if (argc != 2)
	{
		ft_putendl("usage : ./test file_name");
		goto Quit;
	}
	if (ft_wolf_init(&w, argv[1]))
		goto Quit;
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_wolf_key(&w, &in);
		ft_draw(&w);
		ft_update_renderer(w.ptr, w.pixels);
		ft_clear_pixels(w.pixels);
	}
	status = EXIT_SUCCESS;
Quit:
	ft_wolf_quit(&w);
	return (status);
}
