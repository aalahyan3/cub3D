/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/21 11:20:32 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int has_aw_wall(int x, int y, int map[10][10])
{
	if((y < 0 || y>= win_hight) && (x <0 || x>=win_width))
		return (1);
	if (map[y / TAIL][x / TAIL] == 1)
		return (1);
	return (0);
}
void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;
	if((y < 0 || y>= win_hight) && (x <0 || x>=win_width))
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void clear_image(t_img *img)
{
    // zero entire buffer
	
    memset(img->addr, 0,
           img->line_length * win_hight);
}
static double normalize_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return angle;
}
double distance_point(double x0, double y0, double x1, double y1)
{
	return (sqrt(((x1 - x0) * (x1 - x0)) + (((y1 - y0)) * ((y1 - y0)))));
}
void draw_line(int x0, int y0, int x1, int y1, t_img *img, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
void horizontal_casting(t_rays *rays, t_player *player, int map[10][10])
{
	double xsteps;
	double ysteps;
	double xintercept;
	double yintercept;
	double new_x;
	double new_y;
	yintercept = floorf(player->y / TAIL) * TAIL;
	if (rays->down)
		yintercept += TAIL;
	xintercept = player->x + ((yintercept - player->y) / tan(rays->ray_angl));
	xsteps = TAIL / tan(rays->ray_angl);
	ysteps = TAIL;
	if (rays->up)
		ysteps *= -1;
	if (xsteps > 0 && rays->left)
		xsteps *= -1;
	if (xsteps < 0 && rays->right)
		xsteps *= -1;
	new_x = xintercept;
	new_y = yintercept;
	while (new_x >= 0 && new_x < win_map_h && new_y >= 0 && new_y < win_map_h)
	{
		if (has_aw_wall(new_x, new_y-rays->up, map))
		{
			rays->Wall_hit_x_h = new_x;
			rays->Wall_hit_y_h = new_y;
			rays->found_hori = 1;
			break;
		}
		else
		{
			new_x += xsteps;
			new_y += ysteps;
		}
	}
}
void vertical_casting(t_rays *rays, t_player *player, int map[10][10])
{
	double xsteps;
	double ysteps;
	double xintercept;
	double yintercept;
	double new_x;
	double new_y;
	xintercept = floorf(player->x / TAIL) * TAIL;
	if (rays->right)
		xintercept += TAIL;
	yintercept = player->y + (xintercept - player->x) * tan(rays->ray_angl);
	xsteps = TAIL;
	ysteps = TAIL * tan(rays->ray_angl);
	if (rays->left)
		xsteps *= -1;
	if (ysteps > 0 && rays->up)
		ysteps *= -1;
	if (ysteps < 0 && rays->down)
		ysteps *= -1;
	new_x = xintercept;
	new_y = yintercept;
	
	while (new_x >= 0 && new_x < win_map_w && new_y >= 0 && new_y < win_hight)
	{
		if (has_aw_wall(new_x - rays->left, new_y, map))
		{
			rays->Wall_hit_x_v = new_x;
			rays->Wall_hit_y_v = new_y;
			rays->found_ver = 1;
			break;
		}
		else
		{
			new_x += xsteps;
			new_y += ysteps;
		}
	}
}
void casting(t_rays *rays, t_player *player, int map[10][10])
{
	horizontal_casting(rays, player, map);
	vertical_casting(rays, player, map);
	
	if (!rays->found_hori)
		rays->hori_distance = __DBL_MAX__;
	if (!rays->found_ver)
		rays->ver_distance = __DBL_MAX__;
	if (rays->found_hori)
		rays->hori_distance = distance_point(player->x, player->y, rays->Wall_hit_x_h, rays->Wall_hit_y_h);
	if (rays->found_ver)
	{
		rays->ver_distance = distance_point(player->x, player->y, rays->Wall_hit_x_v, rays->Wall_hit_y_v);
	}
	rays->rays_dis =rays->ver_distance;
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
void the_3d_projection(t_rays ray, t_img *img, int i)
{
    const double proj_plane = (win_width / 2.0) / tan(FOV / 2.0);
    const int    centerY    = win_hight / 2;

        // correct fish‑eye
        double corr_dist = ray.rays_dis;
        //                  * cos(ray.ray_angl - player->pa);
		printf("look %f\n",corr_dist);
        if (corr_dist <= 0.0001)
          return;
		else
		{
			double stripH = (int)((TAIL / corr_dist) * proj_plane);
        	double drawStartY = centerY - stripH / 2;
        	double drawEndY   = centerY + stripH / 2;
        	if (drawStartY < 0)         drawStartY = 0;
        	if (drawEndY   > win_hight) drawEndY   = win_hight;
        	int x = i;
        	if (x < 0 || x >= win_width)
           	 return;
        	draw_line(
            x,            // x0
            drawStartY,   // y0
            x,            // x1
            drawEndY,     // y1
            img,
            0x00FFFFFF    // wall color
        );
    }
}

void rander_ray(t_player *player, t_img *data, int map[10][10])
{
	t_rays rays;

	int i = 0;
	while (i < player->num_rays)
	{
		init_rays(&rays, player->num_rays, player->pa,i);
		casting(&rays, player, map);
		the_3d_projection(rays,data,i);
		// if (rays.found_ver || rays.found_hori)
		// 	draw_line(player->x, player->y, rays.Wall_hit_x, rays.Wall_hit_y, data, 0xff0000);
		// draw_line(player->x, player->y, player->x + cos(player->pa) * 30, player->y + sin(player->pa) * 30, data, 0x00fff00);
		i++;
	}
	
}
void rander_player(t_player *player, t_img *data, int map[10][10])
{
	// int i, j;
	// int px = player->x - 3;
	// int py = player->y - 3;

	// i = 0;
	// while (i < 6)
	// {
	// 	j = 0;
	// 	while (j < 6)
	// 	{
	// 		my_mlx_pixel_put(data, px + j, py + i, 0xFF000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	rander_ray(player, data, map);
}

void draw(t_all_data *data)
{

	// int i, j;
	// int x0, y0;
	// int color;
	// int border = 0x000000;

	// i = 0;
	// while (i < 10)
	// {
	// 	j = 0;
	// 	while (j < 10)
	// 	{
	// 		x0 = j * TAIL;
	// 		y0 = i * TAIL;
	// 		if (data->map[i][j] == 1)
	// 			color = 0xffffff;
	// 		else
	// 			color = 0x0000;

	// 		for (int yy = 0; yy < TAIL; yy++)
	// 		{
	// 			for (int xx = 0; xx < TAIL; xx++)
	// 				my_mlx_pixel_put(&data->img, x0 + xx, y0 + yy, color);
	// 		}
	// 		draw_line(x0, y0, x0 + 63, y0, &data->img, border);
	// 		draw_line(x0 + 63, y0, x0 + 63, y0 + 63, &data->img, border);
	// 		draw_line(x0 + 63, y0 + 63, x0, y0 + 63, &data->img, border);
	// 		draw_line(x0, y0 + 63, x0, y0, &data->img, border);

	// 		j++;
	// 	}
	// 	i++;
	// }
	clear_image(&data->img);
	rander_player(&data->player, &data->img, data->map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
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

int handle_keys(t_all_data *data)
{
    t_keys keys = data->keys;
    double newx = data->player.x;
    double newy = data->player.y;
    if (keys.left)
    {
        data->player.pa -= 0.04;
        if (data->player.pa < 0)
            data->player.pa += 2 * M_PI;
    }
    if (keys.right)
    {
        data->player.pa += 0.04;
        if (data->player.pa > 2 * M_PI)
            data->player.pa -= 2 * M_PI;
    }
    data->player.pdx = cos(data->player.pa) * data->player.speed;
    data->player.pdy = sin(data->player.pa) * data->player.speed;
    if (keys.w)
    {
        newx += data->player.pdx;
        newy += data->player.pdy;
    }
    if (keys.s)
    {
        newx -= data->player.pdx;
        newy -= data->player.pdy;
    }
    if (keys.a)
    {
        newx += data->player.pdy;
        newy -= data->player.pdx;
    }
    if (keys.d)
    {
        newx -= data->player.pdy;
        newy += data->player.pdx;
    }
    if (!has_aw_wall((int)newx, (int)newy, data->map))
    {
        data->player.x = newx;
        data->player.y = newy;
    }
    draw(data);
    return 0;
}

int	key_press(int keycode, t_all_data *data)
{
	if (keycode == 13)
		data->keys.w = 1;
	if (keycode == 1)
		data->keys.s = 1;
	if (keycode == 0)
		data->keys.a = 1;
	if (keycode == 2)
		data->keys.d = 1;
	if (keycode == 123)
		data->keys.left = 1;
	if (keycode == 124)
		data->keys.right = 1;
	if (keycode == 53)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_all_data *data)
{
	if (keycode == 13)
		data->keys.w = 0;
	if (keycode == 1)
		data->keys.s = 0;
	if (keycode == 0)
		data->keys.a = 0;
	if (keycode == 2)
		data->keys.d = 0;
	if (keycode == 123)
		data->keys.left = 0;
	if (keycode == 124)
		data->keys.right = 0;
	return (0);
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
	data.mlx_win = mlx_new_window(data.mlx, 10 * TAIL , 10* TAIL, "raycasting");
	img.img = mlx_new_image(data.mlx, 10 * TAIL, 10 * TAIL);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	data.img = img;
	player_inite(&player);
	data.player = player;
	memcpy(data.map, map, sizeof(map));
	mlx_hook(data.mlx_win, 2, 1L<<0, key_press,   &data);	
	mlx_hook(data.mlx_win, 3, 1L<<1, key_release, &data);
	mlx_loop_hook(data.mlx, handle_keys, &data);
	draw(&data);
	mlx_loop(data.mlx);
	return (0);
}
