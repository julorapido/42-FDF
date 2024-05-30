/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:03:43 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/30 11:42:57 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	k_hook(int n, t_mlx *f);

int main(int argc, char **argv)
{
	int	c;
	t_mlx	*f;

	f = ((t_mlx *) malloc(1 * sizeof(t_mlx)));
	f->t_f = (t_wireframe *) malloc(1 * sizeof(t_wireframe));
	if (argc < 2 || argc > 2 || !f || !(f->t_f) )
		return (0);
	c = read_fdf(f, argv[1]);
	if (!c)
	{
		clean_exit(f);
		return (0);
	}
	init(f);
	printf("%d by %d MAP \n", f->t_f->width, f->t_f->height);
	//render_tiles(f);
	render_iso(f);
	render(f);
	mlx_hook(f->win, 2, 1L << 0, k_hook, f);
	//mlx_hook(f->win, 4, 1L << 2, hook_mousedown, f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_loop(f->mlx);	
}
