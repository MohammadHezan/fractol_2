/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:10 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/20 16:19:33 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Write a 32-bit color into the image backbuffer at pixel (real, imag).
*/
void	imag_pixel_put(int real, int imag, t_image *img, int color)
{
	int	offset;

	/* Compute byte offset from row stride and pixel size (bits-per-pixel). */
	offset = (imag * img->line_len) + (real * (img->bpp / 8));
	/* Store color in the raw image buffer. */
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

/*
** Convert screen pixel (x, y) into iteration start values.
**
** coords layout:
** coords[0] = z_real
** coords[1] = z_imag
** coords[2] = c_real
** coords[3] = c_imag
*/
static void	init_coords(int x, int y, t_fractol *f, double coords[4])
{
	double	scale;
	double	px;
	double	py;

	/* Keep scaling isotropic by using the shortest screen dimension. */
	if (WIDTH < HEIGHT)
		scale = 4.0 / WIDTH;
	else
		scale = 4.0 / HEIGHT;
	/* Map pixel x to complex real axis with zoom and pan offsets. */
	px = (x - WIDTH / 2.0) * (scale * f->zoom) + f->offset_x;
	/* Map pixel y to complex imaginary axis with zoom and pan offsets. */
	py = (y - HEIGHT / 2.0) * (scale * f->zoom) + f->offset_y;
	/* Julia starts at z = pixel, c = fixed user-supplied parameter. */
	if (!ft_strncmp(f->name, "julia", 5))
	{
		coords[0] = px;
		coords[1] = py;
		coords[2] = f->julia_real;
		coords[3] = f->julia_imag;
	}
	/* Mandelbrot/Burning Ship start at z = 0, c = pixel coordinate. */
	else
	{
		coords[0] = 0;
		coords[1] = 0;
		coords[2] = px;
		coords[3] = py;
	}
}

/*
** One iteration step for the selected fractal formula.
**
** Standard (Mandelbrot/Julia): z = z^2 + c
** Burning Ship: z = (|Re(z)| + i|Im(z)|)^2 + c
*/
static void	iterate(double *coords, t_fractol *fractol)
{
	double	tmp;
	double	abs_zr;
	double	abs_zi;

	/* Use Burning Ship absolute-value variant when requested. */
	if (!ft_strncmp(fractol->name, "burning_ship", 12))
	{
		/* Absolute value per component before squaring. */
		abs_zr = ft_fabs(coords[0]);
		abs_zi = ft_fabs(coords[1]);
		/* Compute next real component first into temp to avoid overwrite. */
		tmp = abs_zr * abs_zr - abs_zi * abs_zi + coords[2];
		/* Update imaginary component using absolute-value terms. */
		coords[1] = 2 * abs_zr * abs_zi + coords[3];
		/* Commit computed real component. */
		coords[0] = tmp;
	}
	/* Default quadratic iteration for Mandelbrot/Julia families. */
	else
	{
		/* Compute next real component first into temp to avoid overwrite. */
		tmp = coords[0] * coords[0] - coords[1] * coords[1] + coords[2];
		/* Update imaginary component from previous z values. */
		coords[1] = 2 * coords[0] * coords[1] + coords[3];
		/* Commit computed real component. */
		coords[0] = tmp;
	}
}

/*
** Compute and draw one pixel using the escape-time algorithm.
*/
void	handle_pixel(int real, int imag, t_fractol *fractol)
{
	double	coords[4];
	int		i;
	int		color;

	/* Initialize z and c values for this screen coordinate. */
	init_coords(real, imag, fractol, coords);
	/* Start iteration counter at zero. */
	i = 0;
	/* Iterate until escape or max iteration cap. */
	while (i < fractol->max_iter)
	{
		/* Escape test uses squared magnitude against threshold. */
		if ((coords[0] * coords[0] + coords[1] * coords[1]) > fractol->escape)
		{
			/* Map escape iteration to a palette color. */
			color = get_color(i, fractol->max_iter, fractol->color_scheme);
			/* Write escaped-point color and stop processing this pixel. */
			imag_pixel_put(real, imag, &fractol->img, color);
			return ;
		}
		/* Apply one fractal iteration step. */
		iterate(coords, fractol);
		/* Advance iteration counter. */
		i++;
	}
	/* Points that never escaped are rendered in black (inside set). */
	imag_pixel_put(real, imag, &fractol->img, BLACK);
}

/*
** Render full frame:
** iterate over all pixels, compute their fractal color, then blit image.
*/
int	fractol_render(t_fractol *fractol)
{
	int	real;
	int	imag;

	/* Start from first row. */
	imag = 0;
	/* Loop through every image row. */
	while (imag < HEIGHT)
	{
		/* Start from first column in current row. */
		real = 0;
		/* Loop through every pixel in current row. */
		while (real < WIDTH)
		{
			/* Compute and draw one pixel. */
			handle_pixel(real, imag, fractol);
			/* Move to next column. */
			real++;
		}
		/* Move to next row. */
		imag++;
	}
	/* Present fully rendered image buffer in window. */
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img_ptr, 0, 0);
	/* Return type required by several MLX callback usages. */
	return (0);
}
