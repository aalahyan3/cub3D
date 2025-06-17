/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:48:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/17 15:02:45 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "raycasting.h"

typedef struct s_minimap
{
	int	width;
	int	height;
	t_img	image;
	int		view_range;
	int		tile_size;
	char	*addr;
	
}	t_minimap;

void	fill_image_white(void *img_ptr, int width, int height, int line_len, int bpp)
{
	char	*addr;
	int		x;
	int		y;
	char	*pixel;

	addr = mlx_get_data_addr(img_ptr, &bpp, &line_len, &x);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			pixel = addr + (y * line_len + x * (bpp / 8));
			*(unsigned int *)pixel = 0xFFFFFF;
			x++;
		}
		y++;
	}
}


void	*get_minimap(t_all_data *data)
{
	t_minimap minimap;

	minimap.width = 64;
	minimap.height = 64;
	minimap.tile_size = 8;
	minimap.view_range = 8;
	minimap.image.img = mlx_new_image(data->mlx, minimap.width, minimap.height);
	minimap.image.addr = mlx_get_data_addr(minimap.image.addr, &minimap.image.bits_per_pixel, &minimap.image.line_length, &minimap.image.endian);
	fill_image_white(minimap.image.img, minimap.width, minimap.height, minimap.image.line_length, minimap.image.bits_per_pixel);
	return (minimap.image.img);
}
