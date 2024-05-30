/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:16:12 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/30 16:43:12 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//# define arr(x) f->t_f->r_p[x]

void bresLINE(t_mlx *f, int x0, int y0, int x1, int y1, int z)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  int p = 0, p_step = (y1 - y0);
  for (;;){  /* loop */
    set_pixel_color(f, x0, y0, p);
    if (x0 == x1 && y0 == y1)
		break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; p += z * p_step;} /* e_xy+e_y < 0 */
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
	//z = prev_y * -sin(x_angle) + *z * cos(x_angle);
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


/*
void    render_tiles(t_mlx *f)
{
    int x;
    int y;
    int x_p;
    int y_p;
	
    y = 0;
    y_p = (HEIGHT - F_HEIGHT) / 2;
    while(y < f->t_f->height)
    {
		x = 0;
        x_p = (WIDTH - F_WIDTH) / 2;
        while(x < f->t_f->width)
        {  
			bresLINE(f, x_p , y_p, x_p + f->t_f->x_tile , y_p );
			bresLINE(f, x_p, y_p, x_p, y_p + f->t_f->y_tile);
			x++;
            x_p += f->t_f->x_tile;
        }
		bresLINE(f, x_p, y_p, x_p, y_p + f->t_f->y_tile);
        y_p += f->t_f->y_tile;
        y++;(y + x * f->t_f->width) + x
    }
}*/


void	render_iso(t_mlx *f)
{
	
 	int x, y;
    int x_p;
    int y_p;
	
    y = 0;
    y_p = (HEIGHT - F_HEIGHT) / 2;
	f->t_f->r_p = (t_point *) malloc(((sizeof(t_point)) * (f->t_f->width * f->t_f->height)));
    while(y < f->t_f->height)
    {
		x = 0;
        x_p = (WIDTH - F_WIDTH) / 2;
        while(x < f->t_f->width)
        {  
			t_point a;
			a.x = x_p;
			a.y = y_p;

			int z = f->t_f->points[(y * f->t_f->width) + x];
			//printf("(%d:%d) ", a.x, a.y);
			
			t_point p = ft_rotate_z(a.x, a.y, degToRad(45));
			a.x = p.x; 
			a.y = p.y;

			t_point q = ft_rotate_x(a.y, z * -20, (atan(sqrt(2))));
			a.y = q.y;

			//printf(" ==> (%d:%d) \n", a.x, a.y);
			f->t_f->r_p[(y * f->t_f->width) + x] = a;
			x++;
            x_p += f->t_f->x_tile;
        }
		y_p += f->t_f->y_tile;
        y++;
    }

	
	for(int y = 0; y < f->t_f->height; y++)
	{
		for(int x = 0; x < f->t_f->width - 1 ; x++)
		{
			t_point x1 = f->t_f->r_p[(y * f->t_f->width) + x];
			t_point x2 = f->t_f->r_p[(y * f->t_f->width) + (x + 1)];	
			t_point c = f->t_f->r_p[(((y + 1) * f->t_f->width) + x)];

			int z = f->t_f->points[(y * f->t_f->width) + x];
			//printf(" (%d:%d)  (%d:%d) \n",  x1.x, x1.y, x2.x, x2.y);
			//printf("(%d:%d  (%d:%d) \n",  a.x, a.y, a.x, c.y);
			printf(" [x%d:x%d] | [y%d:y%d]\n", 
					(y * f->t_f->width) + x, (y * f->t_f->width) + (x + 1),
					(y * f->t_f->width) + x, (((y + 1) * f->t_f->width) + x)
				);
			if(y < f->t_f->height - 1)
				bresLINE(f, x1.x + F_WIDTH / 2, x1.y, c.x + F_WIDTH / 2, c.y,z);
			bresLINE(f, x1.x + F_WIDTH / 2, x1.y, x2.x + F_WIDTH / 2, x2.y, z);
		}
		printf("================================ \n");
	}

}
