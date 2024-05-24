/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:39:15 by jsaintho          #+#    #+#             */
/*   Updated: 2024/05/24 16:39:48 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

char	*get_next_line(int fd);
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
void	set_pixel_color(t_mlx *f, int x, int y, int n)
{
		char	*dst;
		int		offset;
		int		color;

		n++;
		if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
			return ;
		color = 0x00FFFFFFF;
		
		offset = (y * f->line_length + x * (f->bits_per_pixel / 8));
		dst = f->buf + (offset);
		*(unsigned int*)dst = color;
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

	f->buf = mlx_get_data_addr(f->img, &f->bits_per_pixel, 
			&f->line_length, &f->endian);
}
//  =====================================================
//   					  READ FILE 
//  =====================================================
int	read_fdf(t_mlx *f, char *file_name)
{
	int		fd;
	int		y;
	char	*line_;

	if (!file_name)
		return (0);
	
	fd = open(ft_strjoin("maps/", file_name), O_RDONLY);
	if (fd == -1 || !file_name)
	{
		write(2, "Cannot read file.\n", 18);
		return 0;
	}
	line_ = get_next_line(fd);
	y = 1;
	f->t_f->width = ft_strlen(line_);
	while (line_)
	{
		printf("%s \n", line_);
		line_  = get_next_line(fd);
		y++;
	}
	f->t_f->height = y--;
	close(fd);
	return (1);
}


//  =====================================================
//   					  RENDER 
//  =====================================================
int	render(t_mlx *f)
{
	// SSSS
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return 1;
}
