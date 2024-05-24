/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:56 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/24 16:31:19 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# define FDF_H

# include "mlx.h"
# include <libft.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_wireframe
{
	int		width;
	int		height;

}	t_wireframe;


typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*buf;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_wireframe	*t_f;
}	t_mlx;

// Events
void	key_close(int n, t_mlx *t);
void	clean_exit(t_mlx *t);

// Initialization
void	clean_init(t_mlx *t);
void	init(t_mlx *t);
int		render(t_mlx *t);
int		read_fdf(t_mlx *f, char	*file_name);

// Draw
void	set_pixel_color(t_mlx *t, int x, int y, int n);

// get next line
char	*get_next_line(int fd);
char	*ft_strjoinn(char *s1, char *s2);



#endif
