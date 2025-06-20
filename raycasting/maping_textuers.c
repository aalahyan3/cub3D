/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maping_textuers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:46:24 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 17:04:23 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all_data_struct.h"
#include "raycasting.h"

void set_distance(t_rays *rays)
{
	rays->rays_dis = rays->ver_distance;
	if (rays->ver_distance < rays->hori_distance)
	{
		rays->Wall_hit_x = rays->Wall_hit_x_v;
		rays->Wall_hit_y = rays->Wall_hit_y_v;
		rays->found_hori = 0;
		rays->found_ver = 1;
	}
	else
	{
		rays->found_hori = 1;
		rays->found_ver = 0;
		rays->rays_dis = rays->hori_distance;
		rays->Wall_hit_x = rays->Wall_hit_x_h;
		rays->Wall_hit_y = rays->Wall_hit_y_h;
	}
}
t_img *get_wall_texture(t_all_data *data, t_rays *ray)
{
	double angle = normalize_angle(ray->ray_angl);

	if (ray->found_hori)
	{
		if (angle > 0 && angle < M_PI)
			return &data->map->s_texture;
		else
			return &data->map->n_texture;
	}
	else
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2)
			return &data->map->e_texture;
		else
			return &data->map->w_texture;
	}
}
double get_x_offset(t_rays *ray)
{
	double x_offset;
	
	if (ray->found_hori)
		x_offset = fmod(ray->Wall_hit_x, TILE_SIZE);
	else
		x_offset = fmod(ray->Wall_hit_y, TILE_SIZE);
	return(x_offset);
}