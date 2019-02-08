/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:53:54 by ebatchas          #+#    #+#             */
/*   Updated: 2018/12/08 17:13:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

# include <math.h>

typedef struct	s_complex
{
	double		x;
	double		y;
}				t_complex;

double			ft_module(t_complex *c);
t_complex		ft_add(t_complex a, t_complex b);
t_complex		ft_mult(t_complex *a, t_complex *b);
t_complex		ft_sub(t_complex *a, t_complex *b);
t_complex		ft_div(t_complex *a, t_complex *b);

#endif
