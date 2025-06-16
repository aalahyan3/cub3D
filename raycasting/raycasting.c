/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:57:33 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/16 16:48:16 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	casting(t_rays *rays, t_player *player,t_map *map)
{
	horizontal_casting(rays, player, map);
	vertical_casting(rays, player, map);
	if (!rays->found_hori)
		rays->hori_distance = __DBL_MAX__;
	if (!rays->found_ver)
		rays->ver_distance = __DBL_MAX__;
	if (rays->found_hori)
		rays->hori_distance = distance_point(player->x, player->y,
				rays->Wall_hit_x_h, rays->Wall_hit_y_h);
	if (rays->found_ver)
		rays->ver_distance = distance_point(player->x, player->y,
				rays->Wall_hit_x_v, rays->Wall_hit_y_v);
	rays->rays_dis = rays->ver_distance;
	if (rays->ver_distance < rays->hori_distance)
	{
		rays->Wall_hit_x = rays->Wall_hit_x_v;
		rays->Wall_hit_y = rays->Wall_hit_y_v;
	}
	else
	{
		rays->rays_dis = rays->hori_distance;
		rays->Wall_hit_x = rays->Wall_hit_x_h;
		rays->Wall_hit_y = rays->Wall_hit_y_h;
	}
}

void	draw_wall(int x, int y_start, int y_end, t_img *img)
{
	int	color;
	int	width;
	int	w;

	width = wall_strip;
	color = 0xffffff;
	if (x < 0 || x >= win_width)
		return ;
	if (y_start < 0)
		y_start = 0;
	if (y_end > win_height)
		y_end = win_height;
	while (y_start < y_end)
	{
		w = 0;
		while (w < width && x + w < win_width)
		{
			my_mlx_pixel_put(img, x + w, y_start, color);
			w++;
		}
		y_start++;
	}
}

void	the_3d_projection(t_rays ray, t_img *img, int i, t_player *p)
{
	t_proj	pr;
	double	proj_p;
	int		x;
	float	factor;

	x = i * wall_strip;
	proj_p = (win_width / 2.0) / tan(FOV / 2.0);
	pr.corr_dist = ray.rays_dis * cos(ray.ray_angl - p->pa);
	if (pr.corr_dist <= 0.0001 || x < 0 || x >= win_width)
		return ;
	pr.strip_h = (TAIL / pr.corr_dist) * proj_p;
	pr.draw_s = (win_height / 2) - pr.strip_h / 2;
	pr.draw_e = (win_height / 2) + pr.strip_h / 2;
	if (pr.draw_s < 0)
		pr.draw_s = 0;
	if (pr.draw_e > win_height)
		pr.draw_e = win_height;
	factor = 1.0 - (pr.corr_dist / win_height);
	draw_wall(x, pr.draw_s, pr.draw_e, img);
}

void	start_casting(t_player *player, t_img *img,t_map *map,t_all_data *data)
{
	t_rays	rays;
	int		i;

	i = 0;
	while (i < player->num_rays)
	{
		init_rays(&rays, player->num_rays, player->pa, i);
		casting(&rays, player, map);
		the_3d_projection(rays, img, i, player);
		i++;
	}
}
