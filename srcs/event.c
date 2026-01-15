/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:59:35 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/15 11:46:10 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	morph_julia(t_fractol *fractol, int direction)
{
	const double	step = 0.02;

	if (!ft_strncmp(fractol->name, "julia", 5))
	{
		if (direction == 1)
			fractol->julia_real += step;
		else if (direction == 2)
			fractol->julia_real -= step;
		else if (direction == 3)
			fractol->julia_imag += step;
		else if (direction == 4)
			fractol->julia_imag -= step;
	}
}

int	handle_keypress(int keycode, t_fractol *fractol)
{
	if (keycode == XK_ESCAPE)
		close_window(fractol);
	if (keycode == XK_UP)
		fractol->offset_y -= (0.5 * fractol->zoom);
	else if (keycode == XK_DOWN)
		fractol->offset_y += (0.5 * fractol->zoom);
	else if (keycode == XK_LEFT)
		fractol->offset_x -= (0.5 * fractol->zoom);
	else if (keycode == XK_RIGHT)
		fractol->offset_x += (0.5 * fractol->zoom);
	else if (keycode == XK_PLUS || keycode == XK_EQUAL)
		fractol->max_iter += 10;
	else if (keycode == XK_MINUS || keycode == XK_UNDERSCORE)
		fractol->max_iter -= 10;
	else if (keycode == XK_J)
		morph_julia(fractol, 2);
	else if (keycode == XK_L)
		morph_julia(fractol, 1);
	else if (keycode == XK_I)
		morph_julia(fractol, 3);
	else if (keycode == XK_M)
		morph_julia(fractol, 4);
	fractol_render(fractol);
	return (0);
}

int	handle_mouse(int mouse_button, int mouse_x, int mouse_y, t_fractol *fractol)
{
	double	zoom_factor;
	double	complex_real;
	double	complex_imag;

	if (mouse_button == BUTTON4)
		zoom_factor = 1.2;
	else if (mouse_button == BUTTON5)
		zoom_factor = 0.8;
	else
		return (0);
	complex_real = (mouse_x - WIDTH / 2.0)
		/ (0.5 * fractol->zoom * WIDTH) + fractol->offset_x;
	complex_imag = (mouse_y - HEIGHT / 2.0)
		/ (0.5 * fractol->zoom * HEIGHT) + fractol->offset_y;
	fractol->zoom *= zoom_factor;
	fractol->offset_x = complex_real
		- (mouse_x - WIDTH / 2.0)
		/ (0.5 * fractol->zoom * WIDTH);
	fractol->offset_y = complex_imag
		- (mouse_y - HEIGHT / 2.0)
		/ (0.5 * fractol->zoom * HEIGHT);
	fractol_render(fractol);
	return (0);
}

int	close_window(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(0);
}
