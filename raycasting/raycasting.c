/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:57:33 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/20 12:25:43 by zkhourba         ###   ########.fr       */
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

int get_color(t_rays *ray)
{
	double a = normalize_angle(ray->ray_angl);
	if (ray->found_hori)
	{
		if (a > 0 && a < M_PI)
			return (0x00FF00);
		else
			return (0xFF0000);
	}
	else
	{
		if (a < M_PI_2 || a > 3 * M_PI_2)
			return (0xFFFF00);
		else
			return (0x0000FF);
	}
}
t_img *get_wall_texture(t_all_data *data, t_rays *ray)
{
	double angle = normalize_angle(ray->ray_angl);

	if (ray->found_hori)
	{
		if (angle > 0 && angle < M_PI)
			return &data->mape->s_texture;
		else
			return &data->mape->n_texture;
	}
	else
	{
		if (angle < M_PI_2 || angle > 3 * M_PI_2)
			return &data->mape->e_texture;
		else
			return &data->mape->w_texture;
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
void draw_strip(int x, int y_start, int y_end, double strip_h,
				t_img *img, t_rays *ray, t_all_data *data,int tex_x,t_img *tex)
{
	
	int tex_y;
	int x_offset;
	int w;
	int draw_x;
	double distance_from_top;
	for (w = 0; w < WALL_STRIP_W; w++)
	{
		draw_x = x + w;
		if (draw_x < 0 || draw_x >= WIN_WIDTH)
			continue;
		for (int y = y_start; y < y_end; y++)
		{
			distance_from_top = (y + (strip_h / 2) - ( WIN_HEIGHT / 2));
			tex_y = (int)((distance_from_top / strip_h) * tex->height);
			if (tex_y < 0)
				tex_y = 0;
			else if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			char *p = tex->addr + tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8);
			int color = *(unsigned int *)p;
			my_mlx_pixel_put(img, draw_x, y, color);
		}
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
	draw_strip(x,pr.draw_s,pr.draw_e,pr.strip_h,&data->img,
		data->rays,data,data->tex_data.tex_x,data->tex_data.tex);
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
