/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:32:09 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/15 11:36:24 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if ((2 == argc && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (4 == argc && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractol.name = argv[1];
		if (!ft_strncmp(fractol.name, "julia", 5))
		{
			fractol.julia_real = atof(argv[2]);
			fractol.julia_imag = atof(argv[3]);
		}
		init_fractol(&fractol);
		events_init(&fractol);
		fractol_render(&fractol);
		mlx_loop(fractol.mlx);
	}
	else
	{
		if (!write(2, "Usage: ./fractol mandelbrot | julia real imag\n", 47))
			return (1);
		return (1);
	}
}
