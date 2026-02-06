/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:53:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/02/06 13:02:53 by mohammad-he      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Rainbow palette using phase-shifted sine waves per channel.
** Produces smooth cyclic colors independent of max_iter.
*/
int	scheme_rainbow(int i, int max_iter)
{
	double	r;
	double	g;
	double	b;
	double	frequency;

	/* max_iter is intentionally unused in this sinusoidal palette. */
	(void)max_iter;
	/* Frequency controls speed of color cycling across iterations. */
	frequency = 0.1;
	/* Red channel sinusoid in range [0, 255]. */
	r = sin(frequency * i + 0) * 127 + 128;
	/* Green channel sinusoid phase-shifted for richer gradients. */
	g = sin(frequency * i + 2) * 127 + 128;
	/* Blue channel sinusoid phase-shifted further. */
	b = sin(frequency * i + 4) * 127 + 128;
	/* Pack RGB channels into 0xRRGGBB integer format. */
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

/*
** Fire palette using polynomial interpolation on normalized t.
** Emphasizes warm reds/oranges/yellows.
*/
int	scheme_fire(int i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	/* Normalize iteration index to [0, 1]. */
	t = (double)i / max_iter;
	/* Red channel peaks later for bright flame tips. */
	r = (int)(9 * (1 - t) * t * t * t * 255);
	/* Green channel shapes middle tones (orange/yellow range). */
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	/* Blue channel kept lower to preserve warm palette. */
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	/* Pack RGB channels into 0xRRGGBB integer format. */
	return ((r << 16) | (g << 8) | b);
}

/*
** Ice palette reweights channels for cool cyan/blue gradients.
*/
int	scheme_ice(int i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	/* Normalize iteration index to [0, 1]. */
	t = (double)i / max_iter;
	/* Red channel is reduced to keep palette cold. */
	r = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	/* Green channel shapes aqua transition. */
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	/* Blue channel is stronger for icy appearance. */
	b = (int)(9 * (1 - t) * t * t * t * 255);
	/* Pack RGB channels into 0xRRGGBB integer format. */
	return ((r << 16) | (g << 8) | b);
}

/*
** Purple palette emphasizing blue/magenta transitions.
*/
int	scheme_purple(int i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	/* Normalize iteration index to [0, 1]. */
	t = (double)i / max_iter;
	/* Red contributes magenta highlights. */
	r = (int)(9 * (1 - t) * t * t * t * 255);
	/* Green is reduced to avoid yellowing the palette. */
	g = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	/* Blue channel is dominant for purple tones. */
	b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	/* Pack RGB channels into 0xRRGGBB integer format. */
	return ((r << 16) | (g << 8) | b);
}

/*
** Green palette emphasizing green/cyan transitions.
*/
int	scheme_green(int i, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	/* Normalize iteration index to [0, 1]. */
	t = (double)i / max_iter;
	/* Red channel remains subdued. */
	r = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	/* Green channel has strongest contribution. */
	g = (int)(9 * (1 - t) * t * t * t * 255);
	/* Blue channel balances toward teal in mid-range t. */
	b = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	/* Pack RGB channels into 0xRRGGBB integer format. */
	return ((r << 16) | (g << 8) | b);
}
