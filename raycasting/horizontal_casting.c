/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_casting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:49:39 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	map_bound(t_map *map, t_cast c)
{
	if (c.nx >= 0 && c.ny >= 0
		&& c.nx / TILE_SIZE < map->map_w
		&& c.ny / TILE_SIZE < map->map_h)
		return (1);
	return (0);
}

double	fix_sign(double step, int dir1, int dir2)
{
	if ((step > 0 && dir1) || (step < 0 && dir2))
		step = -step;
	return (step);
}

double	get_step(int neg_dir)
{
	if (neg_dir)
		return (-TILE_SIZE);
	return (TILE_SIZE);
}

void	horizontal_casting(t_rays *rays, t_player *player, t_map *map)
{
	t_cast	c;
	double	a;

	a = rays->ray_angl;
	c.yint = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (rays->down)
		c.yint += TILE_SIZE;
	c.xint = player->x + ((c.yint - player->y) / tan(a));
	c.ystep = get_step(rays->up);
	c.xstep = fix_sign(TILE_SIZE / tan(a), rays->left, rays->right);
	c.nx = c.xint;
	c.ny = c.yint;
	while (map_bound(map, c))
	{
		if (has_aw_wall((int) c.nx, (int) c.ny - rays->up, map))
		{
			rays->wall_hit_x_h = c.nx;
			rays->wall_hit_y_h = c.ny;
			rays->found_hori = 1;
			break ;
		}
		c.nx += c.xstep;
		c.ny += c.ystep;
	}
}
