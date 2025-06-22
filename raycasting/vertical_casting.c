/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_casting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:47:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	get_xstep(int left)
{
	if (left)
		return (-TILE_SIZE);
	return (TILE_SIZE);
}

double	get_ystep(double ang, int up, int down)
{
	double	ystep;

	ystep = TILE_SIZE * tan(ang);
	if ((ystep > 0 && up) || (ystep < 0 && down))
		ystep = -ystep;
	return (ystep);
}

void	vertical_casting(t_rays *rays, t_player *player, t_map *map)
{
	t_vcast	vc;
	double	ang;

	ang = rays->ray_angl;
	vc.xint = floor(player->x / TILE_SIZE) * TILE_SIZE;
	if (rays->right)
		vc.xint += TILE_SIZE;
	vc.yint = player->y + (vc.xint - player->x) * tan(ang);
	vc.xstep = get_xstep(rays->left);
	vc.ystep = get_ystep(ang, rays->up, rays->down);
	vc.nx = vc.xint;
	vc.ny = vc.yint;
	while (vc.nx >= 0 && vc.ny >= 0
		&& vc.nx / TILE_SIZE < map->map_w && vc.ny / TILE_SIZE < map->map_h)
	{
		if (has_aw_wall((int )vc.nx - rays->left, (int)vc.ny, map))
		{
			rays->wall_hit_x_v = vc.nx;
			rays->wall_hit_y_v = vc.ny;
			rays->found_ver = 1;
			break ;
		}
		vc.nx += vc.xstep;
		vc.ny += vc.ystep;
	}
}
