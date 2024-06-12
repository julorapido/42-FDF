/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:42:03 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/12 16:38:39 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	norm_fix(t_mlx *f, int a, int b)
{
	if(f->t_f->has_neg >= 0)
	{
		f->t_f->actual_p_z = f->t_f->points[a];
		f->t_f->actual_p_z_next = f->t_f->points[b];
	}else
	{
		f->t_f->actual_p_z = (f->t_f->points[a] - f->t_f->has_neg);
		f->t_f->actual_p_z_next = (f->t_f->points[b] - f->t_f->has_neg);
	}
}

void	set_fade_settings(t_mlx *f)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	a = 0;
	b = 100000;
	while (i < f->t_f->height * f->t_f->width)
	{
		if (f->t_f->points[i] > a)
			a = f->t_f->points[i];
		if (f->t_f->points[i] < b)
			b = f->t_f->points[i];
		i++;
	}
	f->t_f->slope_len = a - b;
	f->t_f->has_neg = 0;
	if(b < 0)
		f->t_f->has_neg = b;
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

