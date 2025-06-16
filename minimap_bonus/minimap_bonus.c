/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:29:36 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/16 22:07:14 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minimap_bonus.h"

int	get_color(int x, int y , t_all_data *data)
{
	int	map_x;
	int	map_y;

	map_x = data->player.x - x * 
}

void	fill_minimap(t_mmap *minimap, t_all_data *data)
{
	int	x;
	int	y;
	int	color;

	y= 0;
	while (y < MINIMAP_H)
	{
		x = 0;
		while (x < MINIMAP_W)
		{
			color = get_color(x, y, data);
		}
	}
}

void	*get_minimap(t_all_data *data)
{
	t_mmap	minimap;

	minimap.img_ptr = mlx_new_image(data->mlx, MINIMAP_H, MINIMAP_W);
	if (!minimap.img_ptr)
		return (NULL);
	minimap.tile_size = 10;
	minimap.vidible_field = 10;
	fill_minimap(&minimap, data);
}