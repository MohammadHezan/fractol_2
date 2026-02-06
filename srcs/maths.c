/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:56:38 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/23 18:14:15 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Add two complex numbers component-wise.
*/
t_complex	sum_c(t_complex z1, t_complex z2)
{
	t_complex	result;

	/* Real parts add directly. */
	result.real = z1.real + z2.real;
	/* Imaginary parts add directly. */
	result.imag = z1.imag + z2.imag;
	/* Return computed complex sum. */
	return (result);
}

/*
** Square a complex number:
** (a + bi)^2 = (a^2 - b^2) + 2abi
*/
t_complex	square_c(t_complex z)
{
	t_complex	result;

	/* Compute real component of z^2. */
	result.real = (z.real * z.real) - (z.imag * z.imag);
	/* Compute imaginary component of z^2. */
	result.imag = 2 * z.real * z.imag;
	/* Return squared complex value. */
	return (result);
}

/*
** Minimal strncmp replacement required by project constraints.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	/* Zero-length comparison is always equal. */
	if (n == 0)
		return (0);
	/* Start from first character. */
	i = 0;
	/* Advance while characters match and bound is not reached. */
	while (i < n - 1 && s1[i] && s1[i] == s2[i])
		i++;
	/* Return signed difference at first mismatch (or string end). */
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
** Minimal atof replacement supporting:
** - optional leading spaces/tabs,
** - optional sign,
** - integer and fractional decimal parts.
*/
double	ft_atof(const char *str)
{
	double	res[2];
	int		sign;

	/* res[0] stores accumulated value; res[1] stores decimal divisor. */
	res[0] = 0.0;
	res[1] = 1.0;
	/* Default number sign is positive. */
	sign = 1;
	/* Skip leading whitespace accepted by project parser. */
	while (*str == ' ' || *str == '\t')
		str++;
	/* Parse optional sign and update multiplier. */
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	/* Parse integer part digit by digit. */
	while (*str >= '0' && *str <= '9')
		res[0] = res[0] * 10.0 + (*str++ - '0');
	/* Parse optional fractional part after decimal point. */
	if (*str == '.')
	{
		str++;
		/* Each digit increases divisor by factor 10. */
		while (*str >= '0' && *str <= '9')
		{
			res[1] *= 10.0;
			res[0] += (*str++ - '0') / res[1];
		}
	}
	/* Apply sign and return parsed floating-point value. */
	return (sign * res[0]);
}

/*
** Absolute value for doubles.
*/
double	ft_fabs(double n)
{
	/* Flip sign for negative numbers. */
	if (n < 0)
		return (-n);
	/* Positive numbers are returned unchanged. */
	return (n);
}
