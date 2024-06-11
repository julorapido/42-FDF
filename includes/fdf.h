/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:37:56 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/11 15:04:34 by jsaintho         ###   ########.fr       */
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
# define W3 WIDTH/3
# define F_WIDTH 800
# define F_HEIGHT 600
# define M_PI 3.14159265358979323846

//# define ABS(X) X < 0 ? -X : X
//# define SIGN(A) A < 0 ? -1 : 1
#define SNS(a,b) a < b ? (1) : (-1)
# define X_A f->t_f->x_anchor
# define Y_A f->t_f->y_anchor
# define degToRad(a) (a * M_PI / 180.0)
# define fToDeg(f) f < 0 ? (360 - f) : f
# define issou(f) f > 180 ? (-f) : f

/*
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

# define NORM_FIX(a, b)({								\
	int c;												\
	c = (f->t_f->points[a] - f->t_f->points[b] == 0) ? 	\
		(f->t_f->points[a] != 0 ? -1 : 0) : (2);		\
	c;})												\

# define NORM_MACRO(a, b) a == 0 ? (0x00000099) : (a == -1 ? 0x0000FFFf : (255 + b))
*/
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
	int		base_color;
	int		top_color;
	int		sx;
	int		sy;
	int		dx;
	int		dy;
	int		x_anchor;
	int		y_anchor;
	int		x_rot_anchor;
	int		y_rot_anchor;
	double	f_x_rot;
	double	f_y_rot;
	int		actual_p_diff;
	int		actual_p_z;
	int		actual_p_z_next;
	int		actual_p_step;
	int		slope_len;
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


// math
t_point ft_rotate_y(int x, int z, double y_angle);
t_point	ft_rotate_z(int x, int y, double z_angle);
t_point	ft_rotate_x(int y, int z, double x_angle);
void	norm_fix(t_mlx *t, int a, int b);
int		norm_fix_t(t_mlx *f, int a, int b);
void	set_fade_settings(t_mlx *f);

// Events && Utils
void	clean_exit(t_mlx *t);
int		map_size(t_mlx *t, char *map_line);
void	set_wireframe_points(t_mlx *f, char *filename);

// Events
void	rotate_fdf(t_mlx *f, int a);
void	key_close(int n, t_mlx *t);
int		hook_mousedown(int button, int x, int y, t_mlx *f);

// Initialization
void	clean_init(t_mlx *t);
void	init(t_mlx *t);
int		render(t_mlx *t);
int		read_fdf(t_mlx *f, char	*file_name);

// Draw
void	set_pixel_color(t_mlx *t, int x, int y, int n);
void	render_fdf(t_mlx *t);
void	init_iso(t_mlx *t);
void	bresline(t_mlx *f, int x1, int y1, int x2, int y2);


// get next line
char	*get_next_line(int fd);
char	*ft_strjoinn(char *s1, char *s2);

#endif
