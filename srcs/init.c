/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:41:05 by mhaizan           #+#    #+#             */
/*   Updated: 2026/01/15 11:41:45 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error(void)
{
	int	check;

	check = write(2, "Memory allocation failed\n", 26);
	(void)check;
	exit(EXIT_FAILURE);
}

void	image_data(t_fractol *fractol)
{
	fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr,
			&fractol->img.bpp, &fractol->img.line_len, &fractol->img.endian);
	fractol->max_iter = 200;
	fractol->zoom = 1.0;
	fractol->offset_x = 0.0;
	fractol->offset_y = 0.0;
}

void	init_fractol(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (NULL == fractol->mlx)
		error();
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fractol");
	if (NULL == fractol->win)
	{
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		error();
	}
	fractol->img.img_ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (NULL == fractol->img.img_ptr)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		mlx_destroy_display(fractol->mlx);
		free(fractol->mlx);
		error();
	}
	image_data(fractol);
	fractol->c.real = -0.7;
	fractol->c.imag = 0.27015;
	fractol->escape = 4;
	fractol->julia_index = 0;
}

void	events_init(t_fractol *fractol)
{
	mlx_key_hook(fractol->win, handle_keypress, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_hook(fractol->win, 4, 1L << 2, handle_mouse, fractol);
}

int	get_color(int i, int max_iter)
{
	double	r;
	double	g;
	double	b;
	double	frequency;

	(void)max_iter;
	frequency = 0.1;
	r = sin(frequency * i + 0) * 127 + 128;
	g = sin(frequency * i + 2) * 127 + 128;
	b = sin(frequency * i + 4) * 127 + 128;
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}
