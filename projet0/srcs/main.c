/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/02/11 22:22:42 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

int		main(int argc, char *argv[])
{
	t_wolf	f;
	t_input	in;
	int		status;

	status = EXIT_FAILURE;
	if (argc != 2)
	{
		ft_putendl("usage : ./test file_name");
		goto Quit;
	}
	if (ft_wolf_init(&f, argv[1]))
		goto Quit;
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_wolf_draw(&f);
	}
	status = EXIT_SUCCESS;
Quit:
	ft_wolf_quit(&f);
	return (status);
}
