/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:39:00 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_rays(t_rays *rays, int num_rays, double player_ang, int i)
{
	double	start_ang;
	double	angle_step;
	double	ang;

	start_ang = normalize_angle(player_ang - FOV / 2.0);
	angle_step = FOV / num_rays;
	ang = normalize_angle(start_ang + angle_step * i);
	rays->ray_angl = normalize_angle(ang);
	rays->down = (ang > 0 && ang < M_PI);
	rays->up = !rays->down;
	rays->right = (ang < 0.5 * M_PI || ang > 1.5 * M_PI);
	rays->left = !rays->right;
	rays->hori_distance = 0;
	rays->ver_distance = 0;
	rays->wall_hit_x_h = 0;
	rays->wall_hit_y_h = 0;
	rays->wall_hit_x_v = 0;
	rays->wall_hit_y_v = 0;
	rays->wall_hit_y = 0;
	rays->wall_hit_x = 0;
	rays->found_ver = 0;
	rays->found_hori = 0;
	rays->rays_dis = 0;
}

void	player_inite(t_player *player, int x, int y, float angle)
{
	player->x = x * TILE_SIZE + RADIUS;
	player->y = y * TILE_SIZE + RADIUS;
	player->pa = angle;
	player->speed = 5.0;
	player->pdx = cos(player->pa) * player->speed;
	player->pdy = sin(player->pa) * player->speed;
	player->num_rays = WIN_WIDTH ;
	player->shot = 0;
}
