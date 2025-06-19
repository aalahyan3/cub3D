/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:54 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/19 20:06:11 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	ft_put_pixel(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + (y * image->line_length) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < minimap->tile_size)
	{
		i = 0;
		while (i < minimap->tile_size)
		{
			ft_put_pixel(minimap->image, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_circle(t_minimap *minimap, int cx, int cy, int radius, int color)
{
	double	angle;
	int		x;
	int		y;

	angle = 0;
	while (angle < 6.28319)
	{
		x = cx + (int)(radius * cos(angle));
		y = cy + (int)(radius * sin(angle));
		ft_put_pixel(minimap->image, x, y, color);
		angle += 0.01;
	}
}

void	fill_image(t_all_data *data, t_minimap *minimap)
{
	int		x;
	int		y;
	int		map_x;
	int		map_y;
	int		color;
	float	world_x;
	float	world_y;
	float	center_x;
	float	center_y;

	center_x = data->player.x;
	center_y = data->player.y;
	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			world_x = center_x - (minimap->width / 2.0) * (80.0 / minimap->tile_size) + x * (80.0 / minimap->tile_size);
			world_y = center_y - (minimap->height / 2.0) * (80.0 / minimap->tile_size) + y * (80.0 / minimap->tile_size);
			map_x = world_x / 80;
			map_y = world_y / 80;
			if (map_x < 0 || map_x >= data->mape->map_w || map_y < 0 || map_y >= data->mape->map_h || data->mape->arr[map_y][map_x] == ' ')
				color = 0x2e2e2e;
			else if (data->mape->arr[map_y][map_x] == '1')
				color = 0x2e2e2e;
			else if (data->mape->arr[map_y][map_x] == '0' || ft_isalpha(data->mape->arr[map_y][map_x]))
				color = 0xf4e3c1;
			else
				color = 0x888888;
			ft_put_pixel(minimap->image, x, y, color);
			x++;
		}
		y++;
	}
	draw_circle(minimap, minimap->width / 2, minimap->height / 2, 3, 0xff0000);
}




void	*get_minimap(t_all_data *data)
{
	t_minimap	minimap;
	t_img		image;

	minimap.view_range = 4;
	minimap.tile_size = 20;
	minimap.height = minimap.view_range * minimap.tile_size * 2;
	minimap.width = minimap.view_range * minimap.tile_size * 2;

	image.img = mlx_new_image(data->mlx, minimap.width, minimap.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);

	image.width = minimap.width;
	image.height = minimap.height;
	minimap.image = &image;

	fill_image(data, &minimap);
	return (minimap.image->img);
}
