/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_casting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:49:39 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/16 21:01:33 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	fix_sign(double step, int dir1, int dir2)
{
	if ((step > 0 && dir1) || (step < 0 && dir2))
		step = -step;
	return (step);
}

double	get_step(int neg_dir)
{
	if (neg_dir)
		return (-TAIL);
	return (TAIL);
}

void	horizontal_casting(t_rays *rays, t_player *player, t_map *map)
{
	t_cast	c;
	double	a;

	a = rays->ray_angl;
	c.yint = floor(player->y / TAIL) * TAIL;
	if (rays->down)
		c.yint += TAIL;
	c.xint = player->x + ((c.yint - player->y) / tan(a));
	c.ystep = get_step(rays->up);
	c.xstep = fix_sign(TAIL / tan(a), rays->left, rays->right);
	c.nx = c.xint;
	c.ny = c.yint;
	while (c.nx >= 0 && c.ny >= 0 && c.nx / TAIL < map->map_w && c.ny / TAIL < map->map_h)
	{
		if (has_aw_wall((int) c.nx, (int) c.ny - rays->up, map))
		{
			rays->Wall_hit_x_h = c.nx;
			rays->Wall_hit_y_h = c.ny;
			rays->found_hori = 1;
			break ;
		}
		c.nx += c.xstep;
		c.ny += c.ystep;
	}
}