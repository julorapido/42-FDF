/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:37:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/24 15:52:52 by jsaintho         ###   ########.fr       */
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