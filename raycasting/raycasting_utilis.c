/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utilis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:41:55 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 13:32:32 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


int	has_aw_wall(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x / TILE_SIZE >= map->map_w || y / TILE_SIZE >= map->map_h)
		return (1); 

	if (map->arr[y / TILE_SIZE][x / TILE_SIZE] == '1' 
		|| map->arr[y / TILE_SIZE][x / TILE_SIZE] == 'D')
		return (1); 

	return (0);
}
int has_wall_with_radius(int px, int py, int radius, t_map *map)
{
    // top‑left
    if (has_aw_wall(px - radius, py - radius, map))
        return 1;
    // top‑right
    if (has_aw_wall(px + radius, py - radius, map))
        return 1;
    // bottom‑left
    if (has_aw_wall(px - radius, py + radius, map))
        return 1;
    // bottom‑right
    if (has_aw_wall(px + radius, py + radius, map))
        return 1;

    return 0;
}
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
