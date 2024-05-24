/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:37:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/24 18:14:23 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <keys.h>

// =================================
//             CLEAN EXIT
// =================================
void	clean_exit(t_mlx *f)
{
	if(f->img)
	{
		mlx_destroy_image(f->mlx, f->img);
	}	
	if (f->mlx && f->win)
	{
		mlx_loop_end(f->mlx);
		mlx_destroy_window(f->mlx, f->win);
		free(f);
	}
}

// =================================
// 			  KEYBOARD
// =================================
int	k_hook(int k_code, t_mlx *f)
{
	if (k_code == K_ESC)
		clean_exit(f);
	else
	{
		render(f);
	}
	return 0;
}
// ===============================
// 		   MAP CALCULATOR
// ===============================
int	map_size(t_mlx *f, char *map_line)
{
	int	i;
	int c;
	int	l;

	i = 0;
	l = 0;
	while (map_line[i] != '\0')
	{
		c = 1;
		while(ft_isdigit(map_line[i + (c - 1)]))
			c++;
		if (c > 1)
			l++;
		i+= c;
	}
	//
	return (l);
}
