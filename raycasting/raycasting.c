/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:57:33 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 15:07:56 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"


void casting(t_rays *rays, t_player *player, t_map *map)
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
	set_distance(rays);
}


void draw_strip(int x, t_all_data *data,t_proj pr)
{
	double	distance_from_top;
	char	*p;
	int	color;
	int	y;

	y = pr.draw_s;
	while (y < pr.draw_e)
	{
		distance_from_top = (y + (pr.strip_h / 2) - ( WIN_HEIGHT / 2));
		data->tex_data.tex_y = (int)((distance_from_top / pr.strip_h) * data->tex_data.tex->width);
		if (data->tex_data.tex_y < 0)
				data->tex_data.tex_y = 0;
		else if (data->tex_data.tex_y >= data->tex_data.tex->height)
			data->tex_data.tex_y = data->tex_data.tex->height- 1;
		p = data->tex_data.tex->addr + data->tex_data.tex_y * data->tex_data.tex->line_length +
		data->tex_data.tex_x * (data->tex_data.tex->bits_per_pixel / 8);
		color = *(unsigned int *)p;
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}
void draw_wall(int x, t_proj pr, t_all_data *data)
{
	if (x + WALL_STRIP_W < 0 || x >= WIN_WIDTH)
		return;

	data->tex_data.tex = get_wall_texture(data, data->rays);
	data->tex_data.x_offset = get_x_offset(data->rays);
	data->tex_data.tex_x = (int)((data->tex_data.x_offset / TILE_SIZE) * data->tex_data.tex->width);
	if (data->tex_data.tex_x  < 0)
		data->tex_data.tex_x  = 0;
	else if (data->tex_data.tex_x >=data->tex_data.tex->width)
		data->tex_data.tex_x = data->tex_data.tex->width - 1;
	draw_strip(x,data,pr);
}

void the_3d_projection(t_rays ray, t_img *img, int i, t_player *p, t_all_data *data)
{
	t_proj pr;
	double proj_p;
	int x;
	float factor;
	int color;

	data->rays = &ray;
	data->img = *img;
	x = i * WALL_STRIP_W;
	proj_p = (WIN_WIDTH / 2.0) / tan(FOV / 2.0);
	pr.corr_dist = ray.rays_dis * cos(ray.ray_angl - p->pa);
	if (pr.corr_dist <= 0.0001 || x < 0 || x >= WIN_WIDTH)
		return;
	pr.strip_h = (TILE_SIZE / pr.corr_dist) * proj_p;
	pr.draw_s = (WIN_HEIGHT / 2) - pr.strip_h / 2;
	pr.draw_e = (WIN_HEIGHT / 2) + pr.strip_h / 2;
	if (pr.draw_s < 0)
		pr.draw_s = 0;
	if (pr.draw_e > WIN_HEIGHT)
		pr.draw_e = WIN_HEIGHT;
	draw_wall(x, pr,data);
}

void start_casting(t_player *player, t_img *img, t_map *map, t_all_data *data)
{
	t_rays rays;
	int i;

	i = 0;
	while (i < player->num_rays)
	{
		init_rays(&rays, player->num_rays, player->pa, i);
		casting(&rays, player, map);
		the_3d_projection(rays, img, i, player, data);
		i++;
	}
}
