/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:39:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/06/12 16:47:24 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//  ======================================================================
//                            SET PIXEL COLOR                            
//  ======================================================================
//	The MLX image is composed of 32-bits[INTEGER] Pixels.
//	Form of 0xAARRGGBB. 8 bits encode each color component,
//	Alpha (Transparency), Red, Green and Blue.
//	Bit shifting:
//		- BB >> 0   (0x000000FF)
//		- GG >> 8   (0x0000FF00)
//		- RR >> 16  (0x00FF0000)
//		- AA >> 24  (0xAA000000)
void	set_pixel_color(t_mlx *f, int x, int y, int z)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	offset = (y * f->line_length + x * (f->bits_per_pixel / 8));
	dst = f->buf + (offset);
	*(unsigned int *)dst = z;
}

//  =====================================================
//   					      INIT MLX
//  =====================================================
void	init(t_mlx *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		clean_exit(f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Wireframe");
	if (!f->win)
		clean_exit(f);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!(f->img))
		clean_exit(f);
	f->t_f->top_color = 0x0000FFFF;
	f->t_f->base_color = 0x000000FF;
	f->buf = mlx_get_data_addr(f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	f->t_f->f_y_rot = 45;
	f->t_f->f_x_rot = (2);
	f->t_f->y_rot_anchor = 0;
	f->t_f->x_rot_anchor = 0;
	set_fade_settings(f);
}
//  =====================================================
//   					  READ FILE 
//  =====================================================

int	read_fdf(t_mlx *f, char *file_name)
{
	int		fd;
	int		y;
	char	*line_;

	fd = open(ft_strjoin("maps/", file_name), O_RDONLY);
	if (fd == -1 || !file_name)
	{
		write(2, "Cannot read file.\n", 18);
		return (0);
	}
	line_ = get_next_line(fd);
	f->line_length = ft_strlen(line_);
	map_size(f, line_);
	y = 1;
	while (line_)
	{
		ft_putstr_fd(line_, 1);
		line_ = get_next_line(fd);
		y++;
	}
	f->t_f->y_tile = ((int)F_HEIGHT / y - 1);
	f->t_f->height = y--;
	set_wireframe_points(f, file_name);
	close(fd);
	return (1);
}

//  =====================================================
//   					  RENDER 
//  =====================================================
int	render(t_mlx *f)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < HEIGHT)
	{
		x = -1;
		while (x++ < WIDTH)
			set_pixel_color(f, x, y, 0);
	}
	init_iso(f);
	render_fdf(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (1);
}

