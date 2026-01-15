/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:43:10 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/15 11:27:25 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	imag_pixel_put(int real, int imag, t_image *img, int color)
{
	int	offset;

	offset = (imag * img->line_len) + (real * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	init_coords(int x, int y, t_fractol *f, double coords[4])
{
	coords[0] = (x - WIDTH / 2.0) * (4.0 / WIDTH * f->zoom) + f->offset_x;
	coords[1] = (y - HEIGHT / 2.0) * (4.0 / HEIGHT * f->zoom) + f->offset_y;
	if (!ft_strncmp(f->name, "julia", 5))
	{
		coords[2] = f->julia_real;
		coords[3] = f->julia_imag;
	}
	else
	{
		coords[2] = coords[0];
		coords[3] = coords[1];
	}
}

static void	calc_mandel(double *z_r, double *z_i, double c_r, double c_i)
{
	double	tmp;

	tmp = *z_r * *z_r - *z_i * *z_i + c_r;
	*z_i = 2 * *z_r * *z_i + c_i;
	*z_r = tmp;
}

void	handle_pixel(int real, int imag, t_fractol *fractol)
{
	double	coords[4];
	int		i;
	int		color;

	init_coords(real, imag, fractol, coords);
	i = 0;
	while (i < fractol->max_iter)
	{
		if ((coords[0] * coords[0] + coords[1] * coords[1]) > fractol->escape)
		{
			color = get_color(i, fractol->max_iter);
			imag_pixel_put(real, imag, &fractol->img, color);
			return ;
		}
		calc_mandel(&coords[0], &coords[1], coords[2], coords[3]);
		i++;
	}
	imag_pixel_put(real, imag, &fractol->img, BLACK);
}

int	fractol_render(t_fractol *fractol)
{
	int	real;
	int	imag;

	imag = 0;
	while (imag < HEIGHT)
	{
		real = 0;
		while (real < WIDTH)
		{
			handle_pixel(real, imag, fractol);
			real++;
		}
		imag++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img_ptr, 0, 0);
	return (0);
}
