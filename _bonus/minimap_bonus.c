/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:54 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/22 14:12:04 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_bonus.h"

void	ft_put_pixel(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + \
	(y * image->line_length) + (x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_circle(t_minimap *minimap, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	radius_sq;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= pow(radius, 2))
				ft_put_pixel(minimap->image, cx + x, cy + y, 0xff0000);
			x++;
		}
		y++;
	}
}

void	draw_proper_pixel(t_all_data *data, t_minimap *minimap, int x, int y)
{
	int	world_x;
	int	world_y;
	int	color;

	world_x = data->player.x - (minimap->width / 2) * \
	data->minimap_scale + x * data->minimap_scale;
	world_y = data->player.y - (minimap->height / 2) * \
	data->minimap_scale + y * data->minimap_scale;
	if (world_x / TILE_SIZE < 0 || world_x / TILE_SIZE >= data->map->map_w \
	|| world_y / TILE_SIZE < 0 || world_y / TILE_SIZE >= data->map->map_h \
	|| data->map->arr[world_y / TILE_SIZE][world_x / TILE_SIZE] == ' ')
		color = 0x2e2e2e;
	else if (data->map->arr[world_y / TILE_SIZE][world_x / TILE_SIZE] == '1')
		color = 0x2e2e2e;
	else if (data->map->arr[world_y / TILE_SIZE][world_x / TILE_SIZE] == '0' \
	|| ft_isalpha(data->map->arr[world_y / TILE_SIZE][world_x / TILE_SIZE]))
		color = 0xf4e3c1;
	else
		color = 0x888888;
	ft_put_pixel(minimap->image, x, y, color);
}

void	fill_image(t_all_data *data, t_minimap *minimap)
{
	int		x;
	int		y;

	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			draw_proper_pixel(data, minimap, x, y);
			x++;
		}
		y++;
	}
	draw_circle(minimap, minimap->width / 2, minimap->height / 2, 3);
}

void	*get_minimap(t_all_data *data)
{
	t_minimap	minimap;
	t_img		image;

	if (data->keys.up && data->minimap_scale < 20)
		data->minimap_scale++;
	if (data->keys.down && data->minimap_scale > 2)
		data->minimap_scale--;
	data->keys.up = 0;
	data->keys.down = 0;
	minimap.view_range = 8;
	minimap.tile_size = 10;
	minimap.height = minimap.view_range * minimap.tile_size * 2;
	minimap.width = minimap.view_range * minimap.tile_size * 2;
	image.img = mlx_new_image(data->mlx, minimap.width, minimap.height);
	image.addr = mlx_get_data_addr(image.img, \
	&image.bits_per_pixel, &image.line_length, &image.endian);
	image.width = minimap.width;
	image.height = minimap.height;
	minimap.image = &image;
	fill_image(data, &minimap);
	return (minimap.image->img);
}
