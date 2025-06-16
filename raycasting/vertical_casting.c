/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_casting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:47:35 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/16 16:19:44 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

double	get_xstep(int left)
{
	if (left)
		return (-TAIL);
	return (TAIL);
}

double	get_ystep(double ang, int up, int down)
{
	double	ystep;

	ystep = TAIL * tan(ang);
	if ((ystep > 0 && up) || (ystep < 0 && down))
		ystep = -ystep;
	return (ystep);
}

void	vertical_casting(t_rays *rays, t_player *player, t_map *map)
{
	t_vcast	vc;
	double	ang;

	ang = rays->ray_angl;
	vc.xint = floor(player->x / TAIL) * TAIL;
	if (rays->right)
		vc.xint += TAIL;
	vc.yint = player->y + (vc.xint - player->x) * tan(ang);
	vc.xstep = get_xstep(rays->left);
	vc.ystep = get_ystep(ang, rays->up, rays->down);
	vc.nx = vc.xint;
	vc.ny = vc.yint;
	while (vc.nx >= 0 && vc.nx < win_width && vc.ny >= 0 && vc.ny < win_height)
	{
		if (has_aw_wall(vc.nx - rays->left, vc.ny, map))
		{
			rays->Wall_hit_x_v = vc.nx;
			rays->Wall_hit_y_v = vc.ny;
			rays->found_ver = 1;
			break ;
		}
		vc.nx += vc.xstep;
		vc.ny += vc.ystep;
	}
}
