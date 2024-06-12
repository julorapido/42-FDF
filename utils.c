/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:37:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/12 18:15:59 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <keys.h>

// =================================
//             CLEAN EXIT
// =================================
void	clean_exit(t_mlx *f)
{
	if (f->img)
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
		if (k_code == K_LEFT && X_A > -WIDTH / 3)
			X_A -= 5;
		if (k_code == K_RIGHT && X_A < WIDTH / 3)
			X_A += 5;
		if (k_code == K_UP && Y_A > -HEIGHT / 3)
			Y_A -= 5;
		if (k_code == K_DOWN && Y_A < HEIGHT / 3)
			Y_A += 5;
		render(f);
	}
	return (0);
}

// =================================
//				MOUSE
// =================================
int		hook_mousedown(int button, int x, int y, t_mlx *f)
{
	if (button  == MOUSE_WHEEL_UP)
	{
		f->t_f->f_y_rot = fToDeg(f->t_f->f_y_rot + 1);
		f->t_f->y_rot_anchor += -20;
		f->t_f->x_rot_anchor++;
	}
	if (button == MOUSE_WHEEL_DOWN)
	{
		if (f->t_f->f_x_rot < 30)
		{
			f->t_f->f_x_rot = fToDeg(f->t_f->f_x_rot + 0.2);
			f->t_f->y_rot_anchor += 15;
			f->t_f->x_rot_anchor += 15;
		}
	}
	printf("[Y=%f  X=%f]    ANCHORS[x=%d  y=%d] \n", f->t_f->f_y_rot, f->t_f->f_x_rot,
			f->t_f->x_rot_anchor, f->t_f->y_rot_anchor);
	render(f);
	return (0);
}

// ===============================
// 		   MAP CALCULATOR
// ===============================
int	map_size(t_mlx *f, char *map_line)
{
	int	i;
	int	c;
	int	l;

	i = 0;
	l = 0;
	while (map_line[i] != '\0')
	{
		c = 1;
		while (ft_isdigit(map_line[i + (c - 1)]) || map_line[i + (c - 1)] == '-')
			c++;
		if (c > 1)
			l++;
		i += c;
	}
	f->t_f->width = l;
	f->t_f->x_tile = ((int) F_WIDTH / l);
	return (l);
}

// =================================
// 		POINTS INITIALIZATION
// =================================
void	set_wireframe_points(t_mlx *f, char *filename)
{
	int		fd;
	int		k;
	int		l;
	int		c;

	fd = open(ft_strjoin("maps/", filename), O_RDONLY);
	printf("MALLOC POINTS %d \n", (f->t_f->width * f->t_f->height));
	printf("MALLOC CONTENT %d \n", f->line_length * f->t_f->height);
	f->t_f->points = (int *) malloc((f->t_f->width * f->t_f->height) * 4);
	f->file_content = (char *) malloc((f->line_length * f->t_f->height));
	if (fd == -1 || !filename || !f->t_f->points || !f->file_content)
		return ;
	k = 0;
	while (read(fd, &f->file_content[k], 1))
		k++;
	f->file_content[k] = '\0';
	k = 0;
	l = 0;
	while (f->file_content[k] != '\0')
	{
		c = 1;
		while (ft_isdigit(f->file_content[k + (c - 1)]) || f->file_content[k + (c - 1)] == '-')
			c++;
		f->t_f->points[l] = ft_atoi(ft_substr(f->file_content, k, c - 1));
		if (c > 1)
			l++;
		k += c;
	}
	close(fd);
}
