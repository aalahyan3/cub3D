/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:41:55 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/16 16:57:29 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	has_aw_wall(int x, int y, t_map *map)
{
	if ((y < 0 || (y / TAIL) >= map->map_h - 1) || (x < 0 || (x / TAIL) >= map->map_w - 1))
		return (1);
	if (map->arr[(y / TAIL) ][(x / TAIL)] == '1')
	{
		return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((y < 0 || y >= win_height) || (x < 0 || x >= win_width))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img)
{
	memset(img->addr, 0, img->line_length * win_height);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}

double	distance_point(double x0, double y0, double x1, double y1)
{
	return (sqrt(((x1 - x0) * (x1 - x0)) + (((y1 - y0)) * ((y1 - y0)))));
}
