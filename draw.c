/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:16:12 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/04 17:17:16 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//# define arr(x) f->t_f->r_p[x]

void bresLINE(t_mlx *f, int x0, int y0, int x1, int y1, int z)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx =  abs (x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = -abs (y1 - y0);
	sy = y0 < y1 ? 1 : -1; 
	err = dx + dy;
	int y_step = y1 - y0, c = 0x0000FF00/ y_step, d = 0x0000FF00;
	while(1)
	{
		set_pixel_color(f, x0, y0, z == 0 ? 0x00000077 : 
				z == -1 ? 0x0000FFFF : (255 + d));
    	if (x0 == x1 && y0 == y1)
			break;
    	e2 = 2 * err;
    	if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{ 
			err += dx;
			y0 += sy;
			d -= c;
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

t_point	ft_rotate_x(int y, int z, double x_angle)
{
	t_point a;

	a.y = y * cos(x_angle) + z * sin(x_angle);
	a.x = y * -sin(x_angle) + z * cos(x_angle);
	return a;
}

/*
void	ft_rotate_y(int *x, int *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);
}*/

t_point	ft_rotate_z(int x, int y, double z_angle)
{
	t_point a;

	a.x = x * cos(z_angle) - y * sin(z_angle);
	a.y = x * sin(z_angle) + y * cos(z_angle);
	return a;
}


void	render_iso(t_mlx *f)
{
 	int 	x;
    int 	x_p;
	int		y;
    int 	y_p;
	t_point	a;

    y = 0;
    y_p = (HEIGHT - F_HEIGHT) / 2;
	f->t_f->r_p = (t_point *) malloc(((sizeof(t_point)) * (f->t_f->width * f->t_f->height)));
    while(y < f->t_f->height)
    {
		x = 0;
    	x_p = (WIDTH - F_WIDTH) / 2;
        while(x < f->t_f->width)
        {  
			a = ft_rotate_z(x_p, y_p, degToRad(45));
			a.y = (ft_rotate_x(a.y, -13 * (f->t_f->points[(y * f->t_f->width) + x]), (atan(sqrt(2))))).y;

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
	int	y;
	int	x;
	t_point x1;
	t_point x2;

	y = -1;
	while(y++ < f->t_f->height - 1)
	{
		x = -1;
		while(x++ < f->t_f->width - 2)
		{
			int p = (y * f->t_f->width) + x;
			int	Q = ((y + 1) * f->t_f->width) + x;
			x1 = f->t_f->r_p[(y * f->t_f->width) + x];
			x2 = f->t_f->r_p[(y * f->t_f->width) + (x + 1)];	
			t_point c = f->t_f->r_p[(((y + 1) * f->t_f->width) + x)];

			if(y < f->t_f->height - 1)
				bresLINE(f, x1.x + F_WIDTH / 2, x1.y, c.x + F_WIDTH / 2, 
						c.y, f->t_f->points[p] - f->t_f->points[Q] == 0 ? (f->t_f->points[p] != 0 ? -1 : 0)  : (f->t_f->points[p] - f->t_f->points[Q]));
			bresLINE(f, x1.x + F_WIDTH / 2, x1.y, x2.x + F_WIDTH / 2, x2.y,
					f->t_f->points[p] - f->t_f->points[p+1] == 0 ?(f->t_f->points[p] != 0 ? -1 : 0) : (f->t_f->points[p] - f->t_f->points[Q]) );
		}
	}
}
