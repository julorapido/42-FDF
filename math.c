/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:42:03 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/05 14:53:37 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	norm_fix(t_mlx *f, int a, int b)
{
	if (f->t_f->points[a] - f->t_f->points[b] == 0)
	{
		if (f->t_f->points[a] != 0)
			return (-1);
		else
			return (0);
	}else
		return (2);
}

int	norm_fix_t(t_mlx *f, int a, int b)
{
	if (a == 0)
	{
		return (f->t_f->base_color);
	}
	else
	{
		if(a == -1)
			return (f->t_f->top_color);
		else
			return (/*f->t_f->base_color +*/ b);
	}
}

t_point	ft_rotate_x(int y, int z, double x_angle)
{
	t_point a;

	a.y = y * cos(x_angle) + z * sin(x_angle);
	a.x = y * -sin(x_angle) + z * cos(x_angle);
	return (a);
}


t_point ft_rotate_y(int x, int z, double y_angle)
{
	t_point a;

	a.x = x * cos(y_angle) + z * sin(y_angle);
	a.y = x * -sin(y_angle) + z * cos(y_angle); // Z
	return (a);
}

t_point	ft_rotate_z(int x, int y, double z_angle)
{
	t_point	a;

	a.x = x * cos(z_angle) - y * sin(z_angle);
	a.y = x * sin(z_angle) + y * cos(z_angle);
	return (a);
}

