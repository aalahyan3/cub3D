/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:41:55 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 20:17:17 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if ((y < 0 || y >= WIN_HEIGHT) || (x < 0 || x >= WIN_WIDTH))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img)
{
	memset(img->addr, 0, img->line_length * WIN_HEIGHT);
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
