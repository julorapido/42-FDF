/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:37:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/29 12:50:35 by jsaintho         ###   ########.fr       */
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
	f->t_f->width = l;
	f->t_f->x_tile = (int) ((int)F_WIDTH / l);
	return (l);
}



void	set_wireframe_points(t_mlx *f, char *filename)
{
	int		fd;
	int		k;
	int		l;
	int		c;

	fd = open(ft_strjoin("maps/", filename), O_RDONLY);
	f->t_f->points = (int *) malloc((f->t_f->width * f->t_f->height) * sizeof(int));
	f->file_content = (char *) malloc((f->line_length * f->t_f->height) * sizeof(char));
	if (fd == -1 || !filename || !f->t_f->points || !f->file_content)
		return ;
	k = 0;
	while (read(fd, &f->file_content[k], 1))
		k++;
	f->file_content[k] = '\0';
	k = 0;
	l = 0;
	while(f->file_content[k] != '\0')
	{
		c = 1;
		while(ft_isdigit(f->file_content[k + (c - 1)]))
			c++;
		f->t_f->points[l] = ft_atoi(ft_substr(f->file_content, k, c-1)); // slice from k to c - 1
		if (c > 1)
			l++;
		k += c;	
	}
	close(fd);
}
