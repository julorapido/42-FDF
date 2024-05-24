/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:16:12 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/24 18:14:02 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


void    bresenham_segment(t_mlx *f, int x1, int y1, int x2, int y2)
{  
    int dx, dy, p, x, y;  
    dx = x2 - x1;  
    dy = y2 - y1;  
    
    x = x1;  
    y = y1;  
    p = 2 * (dy-dx);  
    while (x<x1)  
    {
        if (p >= 0)  
        {
            set_pixel_color(f, x, y, 0);  
            y++;  
            p += 2*dy - 2*dx;  
        }  
        else  
        {  
            set_pixel_color(f, x, y, 0);
            p += 2 * dy;  
            x++;
        }
    }
}  


void    render_frame()
{
    int x;
    int y;

    while(x < WIDTH)
    {
        while(y < HEIGHT)
        {
            
            y++;
        }
        x++;
    }


}