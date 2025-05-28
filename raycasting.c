/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/28 16:49:16 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"




void casting(t_rays *rays, t_player *player, int map[10][10])
{
	horizontal_casting(rays, player, map);
	vertical_casting(rays, player, map);
	if (!rays->found_hori)
		rays->hori_distance = __DBL_MAX__;
	if (!rays->found_ver)
		rays->ver_distance = __DBL_MAX__;
	if (rays->found_hori)
		rays->hori_distance = distance_point(player->x, 
			player->y, rays->Wall_hit_x_h, rays->Wall_hit_y_h);
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

int shade_color(int color, float factor)
{
	int r = ((color >> 16) & 0xFF) * factor;
	int g = ((color >> 8) & 0xFF) * factor;
	int b = (color & 0xFF) * factor;

	return (r << 16) | (g << 8) | b;
}


static void draw_wall_strip(t_wall w)
{
    while (w.y_start < w.y_end)
    {
        int widx;

        widx = 0;
        while (widx < w.width && w.x + widx < win_width)
        {
            my_mlx_pixel_put(w.img, w.x + widx, w.y_start, w.color);
            widx++;
        }
        w.y_start++;
    }
}

void the_3d_projection(t_rays ray, t_img *img, int i, t_player *p)
{
    t_proj pr;
    double proj_p = (win_width / 2.0) / tan(FOV / 2.0);
    int x = i * wall_strip;
    float factor;

    pr.corr_dist = ray.rays_dis * cos(ray.ray_angl - p->pa);
    if (pr.corr_dist <= 0.0001 || x < 0 || x >= win_width)
        return;
    pr.strip_h = (TAIL / pr.corr_dist) * proj_p;
    pr.draw_s = (win_hight / 2) - pr.strip_h / 2;
    pr.draw_e = (win_hight / 2) + pr.strip_h / 2;
    if (pr.draw_s < 0)
        pr.draw_s = 0;
    if (pr.draw_e > win_hight)
        pr.draw_e = win_hight;
    factor = 1.0 - (pr.corr_dist / win_hight);
    draw_wall(x, wall_strip, pr.draw_s, pr.draw_e, img, shade_color(0xffffff, factor));
}

void start_casting(t_player *player, t_img *data, int map[10][10])
{
	t_rays rays;
	int i;

	i = 0;
	while (i < player->num_rays)
	{
		init_rays(&rays, player->num_rays, player->pa, i);
		casting(&rays, player, map);
		the_3d_projection(rays, data, i, player);
		i++;
	}
}

void draw(t_all_data *data)
{
	clear_image(&data->img);
	start_casting(&data->player, &data->img, data->map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int main(void)
{
	t_img img;
	t_player player;
	t_all_data data;

	int map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 10 * TAIL, 10 * TAIL, "raycasting");
	img.img = mlx_new_image(data.mlx, 10 * TAIL, 10 * TAIL);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	data.img = img;
	player_inite(&player);
	data.player = player;
	memcpy(data.map, map, sizeof(map));
	mlx_hook(data.mlx_win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	draw(&data);
	mlx_loop(data.mlx);
	return (0);
}
