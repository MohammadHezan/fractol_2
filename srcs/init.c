/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:00:00 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/20 16:28:43 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Allocate image backbuffer and retrieve writable pixel metadata.
** This buffer is reused for every full-frame render.
*/
void	image_data(t_fractol *fractol)
{
	/* Allocate an off-screen image with the same dimensions as window. */
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	/* Abort if MLX fails to allocate image memory. */
	if (!fractol->img.img_ptr)
		close_window(fractol, "Error", 3);
	/* Retrieve low-level buffer pointer and layout information. */
	fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr,
			&fractol->img.bpp, &fractol->img.line_len, &fractol->img.endian);
	/* Abort if image data address is unavailable. */
	if (!fractol->img.pixels_ptr)
		close_window(fractol, "Error", 4);
}

/*
** Initialize the fractal runtime:
** - create MLX context and window,
** - allocate image buffer,
** - set default navigation/render parameters.
*/
void	init_fractol(t_fractol *fractol)
{
	/* Create MLX display context (connection to X server). */
	fractol->mlx = mlx_init();
	/* Abort if MLX context creation fails. */
	if (!fractol->mlx)
		close_window(fractol, "Error", 1);
	/* Create window where the fractal image will be presented. */
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, fractol->name);
	/* Abort if window creation fails. */
	if (!fractol->win)
		close_window(fractol, "Error", 2);
	/* Create image buffer and expose raw pixel access. */
	image_data(fractol);
	/* Start at default zoom level (full initial framing). */
	fractol->zoom = 1.0;
	/* Start centered on complex plane origin (real axis). */
	fractol->offset_x = 0.0;
	/* Start centered on complex plane origin (imaginary axis). */
	fractol->offset_y = 0.0;
	/* Default iteration cap balancing speed and visible detail. */
	fractol->max_iter = 100;
	/* Escape threshold uses squared radius (2^2 = 4). */
	fractol->escape = 4;
	/* Start with first palette (rainbow). */
	fractol->color_scheme = 0;
}

/*
** Register MLX hooks:
** - key press,
** - mouse press (wheel),
** - window close event.
*/
void	events_init(t_fractol *fractol)
{
	/* KeyPress event for navigation, iteration, and palette controls. */
	mlx_hook(fractol->win, 2, 1L << 0, handle_keypress, fractol);
	/* ButtonPress event for scroll-wheel zoom. */
	mlx_hook(fractol->win, 4, 1L << 2, handle_mouse, fractol);
	/* DestroyNotify event triggers loop termination when clicking window X. */
	mlx_hook(fractol->win, 17, 0, &mlx_loop_end, fractol->mlx);
}

/*
** Dispatch palette function by active color scheme index.
*/
int	get_color(int i, int max_iter, int color_scheme)
{
	/* Palette 0: sinusoidal rainbow gradient. */
	if (color_scheme == 0)
		return (scheme_rainbow(i, max_iter));
	/* Palette 1: warm fire gradient. */
	else if (color_scheme == 1)
		return (scheme_fire(i, max_iter));
	/* Palette 2: cold ice gradient. */
	else if (color_scheme == 2)
		return (scheme_ice(i, max_iter));
	/* Palette 3: purple-oriented gradient. */
	else if (color_scheme == 3)
		return (scheme_purple(i, max_iter));
	/* Palette 4: green-oriented gradient. */
	else
		return (scheme_green(i, max_iter));
}

/*
** Minimal strlen replacement required by project constraints.
*/
size_t	ft_strlen(const char *str)
{
	size_t	len;

	/* Start count at zero characters. */
	len = 0;
	/* Advance until null terminator. */
	while (str[len])
		len++;
	/* Return number of visible characters. */
	return (len);
}
