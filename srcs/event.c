/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:59:35 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/23 18:14:22 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Adjust Julia constant interactively using keyboard controls:
** - J/L move real component left/right,
** - I/M move imaginary component down/up.
** Changes are clamped to [-2.0, 2.0] to keep values manageable.
*/
static void	update_julia(int keycode, t_fractol *fractol)
{
	/* Julia parameter updates apply only in Julia mode. */
	if (!ft_strncmp(fractol->name, "julia", 5))
	{
		/* Increase real component. */
		if (keycode == XK_L && fractol->julia_real < 2.0)
			fractol->julia_real += 0.02;
		/* Decrease real component. */
		else if (keycode == XK_J && fractol->julia_real > -2.0)
			fractol->julia_real -= 0.02;
		/* Increase imaginary component. */
		else if (keycode == XK_I && fractol->julia_imag < 2.0)
			fractol->julia_imag += 0.02;
		/* Decrease imaginary component. */
		else if (keycode == XK_M && fractol->julia_imag > -2.0)
			fractol->julia_imag -= 0.02;
	}
}

/*
** Keyboard event callback.
**
** Controls:
** - ESC: exit
** - Arrow keys: pan viewport
** - +/-: increase/decrease iteration cap
** - J/L/I/M: tweak Julia constant
** - C: cycle color schemes
*/
int	handle_keypress(int keycode, t_fractol *fractol)
{
	/* Exit request: end MLX loop. */
	if (keycode == XK_ESCAPE)
		mlx_loop_end(fractol->mlx);
	/* Pan left by half current zoom scale. */
	else if (keycode == XK_LEFT)
		fractol->offset_x -= (0.5 * fractol->zoom);
	/* Pan right by half current zoom scale. */
	else if (keycode == XK_RIGHT)
		fractol->offset_x += (0.5 * fractol->zoom);
	/* Pan up by half current zoom scale. */
	else if (keycode == XK_UP)
		fractol->offset_y -= (0.5 * fractol->zoom);
	/* Pan down by half current zoom scale. */
	else if (keycode == XK_DOWN)
		fractol->offset_y += (0.5 * fractol->zoom);
	/* Increase detail level via iteration cap. */
	else if (keycode == XK_PLUS || keycode == XK_EQUAL)
		fractol->max_iter += 10;
	/* Decrease detail level via iteration cap. */
	else if (keycode == XK_MINUS || keycode == XK_UNDERSCORE)
		fractol->max_iter -= 10;
	/* Forward Julia parameter keys to dedicated updater. */
	else if (keycode == XK_J || keycode == XK_L
		|| keycode == XK_I || keycode == XK_M)
		update_julia(keycode, fractol);
	/* Cycle through the five available palettes. */
	else if (keycode == XK_C)
		fractol->color_scheme = (fractol->color_scheme + 1) % 5;
	/* Re-render frame after any interaction. */
	fractol_render(fractol);
	/* Return type required by MLX callback signature. */
	return (0);
}

/*
** Apply mouse-centered zoom:
** 1) map cursor pixel to complex coordinate before zoom,
** 2) change zoom factor,
** 3) recompute offsets so cursor keeps pointing to same complex coordinate.
*/
static void	apply_zoom(int mouse_x, int mouse_y, t_fractol *f, double zf)
{
	double	scale;
	double	cr;
	double	ci;

	/* Preserve square aspect by scaling from shortest image dimension. */
	if (WIDTH < HEIGHT)
		scale = 4.0 / WIDTH;
	else
		scale = 4.0 / HEIGHT;
	/* Compute complex real coordinate currently under cursor. */
	cr = (mouse_x - WIDTH / 2.0) * (scale * f->zoom) + f->offset_x;
	/* Compute complex imaginary coordinate currently under cursor. */
	ci = (mouse_y - HEIGHT / 2.0) * (scale * f->zoom) + f->offset_y;
	/* Apply zoom factor (greater than 1 zooms out in current mapping). */
	f->zoom *= zf;
	/* Recenter horizontal offset so cursor anchor remains stable. */
	f->offset_x = cr - (mouse_x - WIDTH / 2.0) * (scale * f->zoom);
	/* Recenter vertical offset so cursor anchor remains stable. */
	f->offset_y = ci - (mouse_y - HEIGHT / 2.0) * (scale * f->zoom);
}

/*
** Mouse event callback.
** Scroll wheel adjusts zoom and triggers re-render.
*/
int	handle_mouse(int button, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;

	/* Wheel-down button code: zoom out. */
	if (button == BUTTON5)
		zoom_factor = 1.1;
	/* Wheel-up button code: zoom in. */
	else if (button == BUTTON4)
		zoom_factor = 0.9;
	/* Ignore all other mouse buttons. */
	else
		return (0);
	/* Update zoom and offsets with cursor-centered transform. */
	apply_zoom(x, y, fractol, zoom_factor);
	/* Draw updated frame after zoom state change. */
	fractol_render(fractol);
	/* Return type required by MLX callback signature. */
	return (0);
}

/*
** Central cleanup/exit helper.
** Frees MLX resources when available, optionally prints a message, then exits.
*/
int	close_window(t_fractol *fractol, char *msg, int code)
{
	ssize_t	written;

	/* Guard resource cleanup in case of partial initialization. */
	if (fractol)
	{
		/* Destroy image buffer if it exists. */
		if (fractol->img.img_ptr)
			mlx_destroy_image(fractol->mlx, fractol->img.img_ptr);
		/* Destroy window if it exists. */
		if (fractol->win)
			mlx_destroy_window(fractol->mlx, fractol->win);
		/* End loop and release MLX context when available. */
		if (fractol->mlx)
		{
			mlx_loop_end(fractol->mlx);
			free(fractol->mlx);
		}
	}
	/* Print optional message to stderr (used by usage/error paths). */
	if (msg)
	{
		written = write(2, msg, ft_strlen(msg));
		(void)written;
	}
	/* Terminate process with provided exit code. */
	exit(code);
}
