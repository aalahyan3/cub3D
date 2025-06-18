/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:54 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/18 17:03:12 by aalahyan         ###   ########.fr       */
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
	int	tile_x;
	int	tile_y;
	int	map_x;
	int	map_y;
	int	color;

	float	player_tx = data->player.x / 80;
	float	player_ty = data->player.y / 80;
	int	view = minimap->view_range;

	tile_y = 0;
	while (tile_y < view * 2)
	{
		tile_x = 0;
		while (tile_x < view * 2)
		{
			map_x = player_tx - view + tile_x;
			map_y = player_ty - view + tile_y;
			if (map_x < 0 || map_x >= data->mape->map_w || map_y < 0 || map_y >= data->mape->map_h || data->mape->arr[map_y][map_x] == ' ')
				color = 0x222222;
			else if (data->mape->arr[map_y][map_x] == '1')
				color = 0x000000;
			else if (data->mape->arr[map_y][map_x] == '0' || ft_isalpha(data->mape->arr[map_y][map_x]))
				color = 0xffffff;
			else
				color = 0x888888;
			draw_tile(minimap, tile_x * minimap->tile_size, tile_y * minimap->tile_size, color);
			tile_x++;
		}
		tile_y++;
	}
	draw_circle(minimap, minimap->width / 2, minimap->height / 2, 3, 0xff0000);
}

void	*get_minimap(t_all_data *data)
{
	t_minimap	minimap;
	t_img		image;

	minimap.view_range = 5;
	minimap.tile_size = 10;
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
