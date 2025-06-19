/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:57:33 by zkhourba          #+#    #+#             */
/*   Updated: 2025/06/19 16:22:52 by zkhourba         ###   ########.fr       */
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

void draw_wall(int x, int y_start, int y_end, double strip_h,
               t_img *img, t_rays *ray, t_all_data *data)
{
    t_img    *tex;
    int       tex_x, tex_y;
    double    wall_hit;
    int       wall_h_clamped = y_end - y_start;
  
    double    y_offset = (strip_h - wall_h_clamped) / 2.0;
    int       w, draw_x;

    if (x + WALL_STRIP_W < 0 || x >= WIN_WIDTH)
        return ;

    tex = get_wall_texture(data, ray);
    // fractional hit along the wall face [0..TAIL)
    if (ray->found_hori)
        wall_hit = fmod(ray->Wall_hit_x, TILE_SIZE);
    else
        wall_hit = fmod(ray->Wall_hit_y, TILE_SIZE);

    // base X in texture
    tex_x = (int)((wall_hit / TILE_SIZE) * tex->width);
    if (tex_x < 0)               
		tex_x = 0;
    else if (tex_x >= tex->width)
		tex_x = tex->width - 1;

    // for each sub-column in this strip
    for (w = 0; w < WALL_STRIP_W; w++)
    {
        draw_x = x + w;
        if (draw_x < 0 || draw_x >= WIN_WIDTH)
            continue;

        // draw vertical span
        for (int y = y_start; y < y_end; y++)
        {
            // d runs from 0..strip_h
            double d = (y - y_start) + y_offset;
            tex_y = (int)((d / strip_h) * tex->height);

            // clamp tex_y
            if (tex_y < 0)               tex_y = 0;
            else if (tex_y >= tex->height) tex_y = tex->height - 1;

            // fetch pixel
            char *p = tex->addr
              + tex_y * tex->line_length
              + tex_x * (tex->bits_per_pixel / 8);
            int color = *(unsigned int *)p;
            my_mlx_pixel_put(img, draw_x, y, color);
        }
    }
}

void	the_3d_projection(t_rays ray, t_img *img, int i, t_player *p,t_all_data *data)
{
	t_proj	pr;
	double	proj_p;
	int		x;
	float	factor;
	int color;
	x = i * WALL_STRIP_W;
	proj_p = (WIN_WIDTH / 2.0) / tan(FOV / 2.0);
	pr.corr_dist = ray.rays_dis * cos(ray.ray_angl - p->pa);
	if (pr.corr_dist <= 0.0001 || x < 0 || x >= WIN_WIDTH)
		return ;
	pr.strip_h = (TILE_SIZE / pr.corr_dist) * proj_p;
	pr.draw_s = (WIN_HEIGHT / 2) - pr.strip_h / 2;
	pr.draw_e = (WIN_HEIGHT / 2) + pr.strip_h / 2;
	if (pr.draw_s < 0)
		pr.draw_s = 0;
	if (pr.draw_e > WIN_HEIGHT)
		pr.draw_e = WIN_HEIGHT;
	
	draw_wall(x, pr.draw_s, pr.draw_e,pr.strip_h, img,&ray,data);
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
		the_3d_projection(rays, img, i, player,data);
		i++;
	}
}
