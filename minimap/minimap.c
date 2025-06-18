/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:54 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/18 11:14:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

// int	get_x_map(int x, int y)
// {
	
// }

// void	fill_image(t_minimap *minimap, t_all_data *data)
// {
// 	int	x;
// 	int	y;
// 	int	x_map;
// 	int	y_map;

// 	y = 0;
// 	while (y < minimap->height / minimap->tile_size)
// 	{
// 		x = 0;
// 		while (x < minimap->width / minimap->tile_size)
// 		{
// 			int	x_map = get_x_map(x, y)
// 		}
// 	}
// }

void	*get_minimap(t_all_data *data)
{
	t_minimap minimap;
	t_img	image;

	minimap.height = 160;
	minimap.width = 160;
	image.img = mlx_new_image(data->mlx, minimap.width, minimap.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.bits_per_pixel, &image.endian);
	minimap.image = &image;
	minimap.view_range = 8;
	minimap.tile_size = 10;
	// fill_image(&minimap, data);
	return (NULL);
}