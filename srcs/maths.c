/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:56:38 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/15 11:24:03 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / (old_max) + new_min);
}

t_complex	sum(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.imag = z1.imag + z2.imag;
	return (result);
}

t_complex	square(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.imag * z.imag);
	result.imag = 2 * z.real * z.imag;
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
