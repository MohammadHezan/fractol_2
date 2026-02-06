/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:32:23 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/20 16:19:32 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Fractol public header.
**
** This file centralizes:
** - shared constants (window size, colors, key codes, mouse codes),
** - core data structures used by the renderer,
** - function prototypes exposed across translation units.
**
** Keeping this contract explicit helps contributors navigate the codebase
** quickly and understand where state is stored and how modules interact.
*/

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"

/* Window dimensions used by MiniLibX when creating the render surface. */
# define WIDTH 800
# define HEIGHT 800

/* Color constant used for points that do not escape (inside set). */
# define BLACK       0x000000

/* Keyboard keycodes (X11/Linux) used by the event handler. */
# define XK_ESCAPE 65307
# define XK_LEFT 65361
# define XK_RIGHT 65363
# define XK_UP 65362
# define XK_DOWN 65364
# define XK_PLUS 65451
# define XK_MINUS 65453
# define XK_EQUAL 61
# define XK_UNDERSCORE 45
# define XK_J 106
# define XK_L 108
# define XK_I 105
# define XK_M 109
# define XK_SPACE 32
# define XK_C 99

/* Mouse wheel buttons on X11: down/up for zoom control. */
# define BUTTON5 5
# define BUTTON4 4

/*
** Complex number with real and imaginary parts.
** Used for fractal iteration math.
*/
typedef struct s_complex
{
	double			real;
	double			imag;
}					t_complex;

/*
** Raw image metadata returned by MiniLibX.
** pixels_ptr points to the image memory buffer.
*/
typedef struct s_image
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_image;

/*
** Global runtime state for one fractal session.
**
** mlx / win:
**   MiniLibX context and window handles.
** img:
**   Backbuffer image used for pixel drawing.
** max_iter:
**   Escape-time iteration limit (quality/detail control).
** zoom / offset_x / offset_y:
**   Viewport transform from screen space to complex plane.
** c:
**   Reserved complex parameter slot (kept for extensibility).
** name:
**   Selected fractal type ("mandelbrot", "julia", "burning_ship").
** escape:
**   Escape radius squared threshold.
** julia_real / julia_imag:
**   Julia constant components when in Julia mode.
** julia_index:
**   Reserved index slot (kept for extensibility).
** color_scheme:
**   Active palette index.
*/
typedef struct s_fractol
{
	void			*mlx;
	void			*win;
	t_image			img;
	int				max_iter;
	double			zoom;
	double			offset_x;
	double			offset_y;
	t_complex		c;
	char			*name;
	int				escape;
	double			julia_real;
	double			julia_imag;
	int				julia_index;
	int				color_scheme;
}					t_fractol;

/* Event callbacks and application lifecycle helpers. */
int			handle_mouse(int mouse_button, int mouse_x, int mouse_y,
				t_fractol *fractol);
int			close_window(t_fractol *fractol, char *msg, int code);
int			handle_keypress(int keycode, t_fractol *fractol);

/* Initialization and setup routines. */
void		init_fractol(t_fractol *fractol);
void		events_init(t_fractol *fractol);
void		image_data(t_fractol *fractol);

/* Complex arithmetic utilities (used by fractal math paths). */
t_complex	sum_c(t_complex z1, t_complex z2);
t_complex	square_c(t_complex z);

/* Rendering pipeline entry points and low-level pixel write function. */
void		handle_pixel(int real, int imag, t_fractol *fractol);
int			fractol_render(t_fractol *fractol);
void		imag_pixel_put(int real, int imag, t_image *img, int color);

/* Minimal libc-like helpers required by project constraints. */
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			get_color(int i, int max_iter, int color_scheme);
int			scheme_rainbow(int i, int max_iter);
int			scheme_fire(int i, int max_iter);
int			scheme_ice(int i, int max_iter);
int			scheme_purple(int i, int max_iter);
int			scheme_green(int i, int max_iter);
double		ft_atof(const char *str);
double		ft_fabs(double n);
size_t		ft_strlen(const char *str);

#endif
