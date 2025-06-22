/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:16:48 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	has_aw_wall(int x, int y, t_map *map)
{
	if (x < 0 || y < 0
		||x / TILE_SIZE >= map->map_w
		|| y / TILE_SIZE >= map->map_h)
		return (1);
	if (map->arr[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (1);
	return (0);
}

int	has_wall_with_radius(int px, int py, int radius, t_map *map)
{
	if (has_aw_wall(px - radius, py - radius, map))
		return (1);
	if (has_aw_wall(px + radius, py - radius, map))
		return (1);
	if (has_aw_wall(px - radius, py + radius, map))
		return (1);
	if (has_aw_wall(px + radius, py + radius, map))
		return (1);
	return (0);
}
