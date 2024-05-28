/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:16:12 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/28 16:22:15 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void bresLINE(t_mlx *f, int x0, int y0, int x1, int y1)
{
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    set_pixel_color(f, x0, y0, 0);
    if (x0 == x1 && y0 == y1)
		break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
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




void    render_tiles(t_mlx *f)
{
    int x;
    int y;
    int x_p;
    int y_p;
	
    y = 0;
    y_p = 0;
    while(y < f->t_f->height)
    {
        x = x_p = 0;
        while(x < f->t_f->width)
        {
			int xx =ROTATE_Z_X(x_p + f->t_f->x_tile, y_p, 45);
			int yy = ROTATE_X_Y(ROTATE_Z_Y(x_p + f->t_f->x_tile, y_p, 45), atan(sqrt(2)), 10);
			if(f->t_f->points[(y * f->t_f->width) + x] == 0)
				bresLINE(f, x_p, y_p, x_p + f->t_f->x_tile, y_p);
			else{
				bresLINE(f, x_p, y_p, xx, yy);
			}
			printf("(%d:%d) = %d \n", x, y, f->t_f->points[(y * f->t_f->width) + x]);
			bresLINE(f, x_p, y_p, x_p, y_p + f->t_f->y_tile);
            x++;
            x_p += f->t_f->x_tile;
        }
        y_p += f->t_f->y_tile;
        y++;
    }
}
