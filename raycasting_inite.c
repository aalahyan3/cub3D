/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_inite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:39:00 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/28 16:40:28 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void init_rays(t_rays *rays, int num_rays, double player_ang, int i)
{
	double start_ang = normalize_angle(player_ang - FOV / 2.0);
	double angle_step = FOV / num_rays;
	double ang = normalize_angle(start_ang + angle_step * i);
	rays->ray_angl = normalize_angle(ang);
	rays->down = (ang > 0 && ang < M_PI);
	rays->up = !rays->down;
	rays->right = (ang < 0.5 * M_PI || ang > 1.5 * M_PI);
	rays->left = !rays->right;
	rays->hori_distance = 0;
	rays->ver_distance = 0;
	rays->Wall_hit_x_h = 0;
	rays->Wall_hit_y_h = 0;
	rays->Wall_hit_x_v = 0;
	rays->Wall_hit_y_v = 0;
	rays->Wall_hit_y = 0;
	rays->Wall_hit_x = 0;
	rays->found_ver = 0;
	rays->found_hori = 0;
	rays->rays_dis = 0;
}
void player_inite(t_player *player)
{
	player->x = win_width / 2;
	player->y = win_hight / 2;
	player->pa = 0.0;
	player->speed = 3.0;
	player->pdx = cos(player->pa) * player->speed;
	player->pdy = sin(player->pa) * player->speed;
	player->num_rays = win_width / wall_strip;
}