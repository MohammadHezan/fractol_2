/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:32:09 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/23 18:28:16 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Validate a floating-point literal in the restricted project format:
**   [sign]digits.digits
** Examples accepted: -0.7, +2.0, 1.234
** Examples rejected: ".", "1", "1.", "abc"
*/
static int	is_valid_float(const char *str)
{
	int	i;
	int	has_dot;

	/* Start scanning from the first character. */
	i = 0;
	/* Track whether a decimal point was found. */
	has_dot = 0;
	/* Skip optional sign prefix. */
	if (str[i] == '-' || str[i] == '+')
		i++;
	/* Reject strings that start with dot or become empty after sign. */
	if (str[i] == '.' || !str[i])
		return (0);
	/* Consume integer part. */
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	/* Consume the mandatory decimal separator. */
	if (str[i] == '.')
	{
		has_dot = 1;
		i++;
	}
	/* Require at least one digit after decimal point if dot exists. */
	if (has_dot && !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	/* Consume fractional part. */
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	/* Valid only if format used a dot and no extra trailing characters. */
	return (has_dot && !str[i]);
}

/*
** Parse Julia constant from CLI arguments and clamp both components
** to the interval [-2.0, 2.0] to keep exploration values bounded.
*/
static void	init_julia_params(t_fractol *fractol, char **argv)
{
	/* Parse real part from argv[2]. */
	fractol->julia_real = ft_atof(argv[2]);
	/* Parse imaginary part from argv[3]. */
	fractol->julia_imag = ft_atof(argv[3]);
	/* Clamp real part lower bound. */
	if (fractol->julia_real < -2.0)
		fractol->julia_real = -2.0;
	/* Clamp real part upper bound. */
	if (fractol->julia_real > 2.0)
		fractol->julia_real = 2.0;
	/* Clamp imaginary part lower bound. */
	if (fractol->julia_imag < -2.0)
		fractol->julia_imag = -2.0;
	/* Clamp imaginary part upper bound. */
	if (fractol->julia_imag > 2.0)
		fractol->julia_imag = 2.0;
}

/*
** Central startup routine:
** 1) initialize MLX objects and runtime state,
** 2) register input hooks,
** 3) render first frame,
** 4) enter MLX event loop.
*/
static void	run_fractol(t_fractol *fractol)
{
	/* Allocate MLX context, window, and image buffer. */
	init_fractol(fractol);
	/* Bind keyboard/mouse/window events. */
	events_init(fractol);
	/* Draw initial frame before loop starts. */
	fractol_render(fractol);
	/* Hand over control to MLX event loop. */
	mlx_loop(fractol->mlx);
	/* Fallback cleanup after loop exits. */
	close_window(fractol, NULL, 0);
}

/*
** Program entry point.
**
** Supported signatures:
**   ./fractol mandelbrot
**   ./fractol burning_ship
**   ./fractol julia <real> <imaginary>
*/
int	main(int argc, char **argv)
{
	t_fractol	fractol;

	/* Handle Mandelbrot and Burning Ship modes (single-name argument). */
	if (2 == argc && (!ft_strncmp(argv[1], "mandelbrot\0", 11)
			|| !ft_strncmp(argv[1], "burning_ship\0", 13)))
	{
		/* Store selected fractal name for downstream logic checks. */
		fractol.name = argv[1];
		/* Initialize and run interactive session. */
		run_fractol(&fractol);
	}
	/* Handle Julia mode with two validated floating-point parameters. */
	else if (4 == argc && !ft_strncmp(argv[1], "julia\0", 6)
		&& is_valid_float(argv[2]) && is_valid_float(argv[3]))
	{
		/* Store selected fractal name for downstream logic checks. */
		fractol.name = argv[1];
		/* Parse and clamp Julia constant from CLI. */
		init_julia_params(&fractol, argv);
		/* Initialize and run interactive session. */
		run_fractol(&fractol);
	}
	else
	{
		/* Initialize pointers to safe values before error cleanup path. */
		fractol.mlx = NULL;
		fractol.win = NULL;
		fractol.img.img_ptr = NULL;
		/* Print usage and exit on invalid invocation. */
		close_window(NULL,
			"Usage: ./fractol mandelbrot | burning_ship | julia <r> <i>\n",
			1);
	}
	/* Unreachable in normal flow (mlx_loop is blocking), kept for clarity. */
	return (0);
}
