/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:16:12 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/05 17:43:41 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresline(t_mlx *f, int x0, int y0, int x1, int y1, int z)
{
	int	err;
	int	e2;
	int	d;
	int	y_step;

	f->t_f->dx = abs(x1 - x0);
	f->t_f->sx = SNS(x0, x1);
	f->t_f->dy = -(abs(y1 - y0));
	f->t_f->sy = SNS(y0, y1);
	err = f->t_f->dx + f->t_f->dy;
	y_step = abs(y1 - y0);
	d = f->t_f->top_color;
	while (1)
	{
		set_pixel_color(f, x0, y0, norm_fix_t(f, z, d));
		if (x0 == x1 && y0 == y1)
			break ;
    	e2 = 2 * err;
		if (e2 >= f->t_f->dy)
		{
			err += f->t_f->dy;
			x0 += f->t_f->sx;
		}
		if (e2 <= f->t_f->dx)
		{ 
			err += f->t_f->dx;
			y0 += f->t_f->sy;
			d -= f->t_f->top_color / y_step;
		}
	}
}

/*
3d Rotation matrice:
		[1	0	0]			[.	0	.]			[.	.	0]
Rx(θ) = [0	.	.]  Ry(θ) = [0	1	0]  Rz(θ) = [.	.	0]
		[0	.	.]			[.	0	.]			[0	0	1]

Example rotation on Z-axis:
	    [cos(θ)  -sin(θ)  0]	   [x]     [cos(θ)x + -sin(θ)y]
Rz(θ) = [sin(θ)  cos(θ)   0]	=  [y]  =  [sin(θ)x +  cos(θ)y]
	    [0  		0  	 	 1]	   [z]     [        z         ]
*/
void	init_iso(t_mlx *f)
{
	int		x;
	int		x_p;
	int		y;
	int		y_p;
	t_point	a;

	y = 0;
	y_p = (HEIGHT - F_HEIGHT) / 2;
	f->t_f->r_p = (t_point *) malloc(sizeof(t_point) * (f->t_f->width * f->t_f->height));
	while (y < f->t_f->height)
	{
		x = 0;
		x_p = (WIDTH - F_WIDTH) / 2;
		while (x < f->t_f->width)
		{
			a = ft_rotate_z(x_p, y_p, degToRad(45));
			a.y = (ft_rotate_x(a.y, -7 * (f->t_f->points[(y * f->t_f->width) + x]), (atan(sqrt(2))))).y;
			f->t_f->r_p[(y * f->t_f->width) + x] = a;
			x++;
			x_p += f->t_f->x_tile;
		}
		y_p += f->t_f->y_tile;
		y++;
	}
}

void	render_fdf(t_mlx *f)
{
	int		y;
	int		x;
	t_point	x1;
	t_point	x2;
	t_point	y2;

	y = -1;	
	while (y++ < f->t_f->height - 1)
	{
		x = -1;
		while (x++ < f->t_f->width - 2)
		{
			x1 = f->t_f->r_p[(y * f->t_f->width) + x];
			x2 = f->t_f->r_p[(y * f->t_f->width) + x + 1];
			y2 = f->t_f->r_p[((y + 1) * f->t_f->width) + x];
			if (y < f->t_f->height - 1)
				bresline(f, x1.x + W3 + X_A, x1.y + Y_A, y2.x + W3 + X_A, y2.y + Y_A, 
					norm_fix(f, (y * f->t_f->width) + x, ((y + 1) * f->t_f->width) + x));
			bresline(f, x1.x + W3 + X_A, x1.y + Y_A, x2.x + W3 + X_A, x2.y + Y_A, 
					norm_fix(f, (y * f->t_f->width) + x, (y * f->t_f->width) + x + 1));
		}
	}
}

