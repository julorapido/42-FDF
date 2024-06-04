/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:56 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/04 16:52:28 by jsaintho         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1080

# define F_WIDTH 800
# define F_HEIGHT 600
#define M_PI       3.14159265358979323846

# define ABS(X) X < 0 ? -X : X
# define SIGN(A) A < 0 ? -1 : 1
# define degToRad(a) (a * M_PI / 180.0)

# define ROTATE_Z_X(x, y, a)({			\
	int x2;								\
	x2 = x * cos(a) - y * sin(a);	 	\
	x2;})								\

# define ROTATE_Z_Y(x, y, a)({			\
	int y2;								\
	y2 = x * sin(a) + y * cos(a); 		\
	y2;})								\

# define ROTATE_X_Y(y, z, a)({			\
	int y2;								\
	y2 = y * cos(a) + z * sin(a);		\
	y2;})								\

typedef struct s_point
{
	int x;
	int y;
}				t_point;

typedef struct s_wireframe
{
	int		width;
	int		height;
	int		x_tile;
	int		y_tile;
	int		*points;
	t_point	*r_p;
	char	*file_content;
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
	char		*file_content;
	t_wireframe	*t_f;
}	t_mlx;

// Events && Utils
void	key_close(int n, t_mlx *t);
void	clean_exit(t_mlx *t);
int		map_size(t_mlx *t, char *map_line);
void	set_wireframe_points(t_mlx *f, char *filename);

// Initialization
void	clean_init(t_mlx *t);
void	init(t_mlx *t);
int		render(t_mlx *t);
int		read_fdf(t_mlx *f, char	*file_name);

// Draw
void	set_pixel_color(t_mlx *t, int x, int y, int n);
void	render_fdf(t_mlx *t);
void	render_iso(t_mlx *t);
void	bresLINE(t_mlx *f, int x1, int y1, int x2, int y2, int z);


// get next line
char	*get_next_line(int fd);
char	*ft_strjoinn(char *s1, char *s2);



#endif
