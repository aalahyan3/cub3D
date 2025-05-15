/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/15 20:35:44 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raycasting.h"

int has_aw_wall(int x, int y, int map[10][10])
{
	if(map[y/TAIL][x/TAIL] == 1)
		return(1);
	return(0);
}
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
	    + (y * data->line_length
	    +  x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
static double normalize_angle(double angle)
{
    angle = fmod(angle, 2.0 * M_PI);   
    if (angle < 0)
        angle += 2.0 * M_PI;
    return angle;
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
		my_mlx_pixel_put(img,x0, y0, color); 
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

void casting(t_rays *rays, t_player *player,int map[10][10])
{
	int xsteps;
	int ysteps;
	int xintercept;
	int	yintercept;
	int	new_x;
	int	new_y;
	yintercept = floorf(player->y / TAIL) * TAIL;
	if(rays->down)
		yintercept += TAIL;
	xintercept = player->x + ((yintercept - player->y) / tan(rays->ray_angl));
	xsteps = TAIL / tan(rays->ray_angl);
	ysteps = TAIL;
	if(rays->up)
		ysteps *= -1; 
	if(xsteps > 0 && rays->left)
		xsteps *= -1;
	if(xsteps < 0 && rays->right)
		xsteps *= -1;
	new_x = xintercept;
	new_y = yintercept;
	if(rays->up)
		new_y--;
	while (new_x >=0 && new_x < win_width && new_y >=0 && new_y < win_hight)
	{
		if(has_aw_wall(new_x,new_y,map))
		{
			rays->Wall_hit_x = new_x;
			rays->Wall_hit_y = new_y;
			rays->found = 1;
			break;
		}
		else
		{
			new_x +=xsteps;
			new_y+= ysteps;
		}
	}
	
}
void init_rays(t_rays *rays,int num_rays,double angle)
{
	int i= 0;
	double	angle_inc =  angle - (FOV / 2);
	while (i < num_rays)
	{
		rays[i].found = 0;
		rays[i].left = 0;
		rays[i].right = 0;
		rays[i].up = 0;
		rays[i].down = 0;
		rays[i].hori_distance = 0;
		rays[i].ray_angl = angle_inc;
		rays[i].ray_angl = normalize_angle(rays[i].ray_angl);
		if(rays[i].ray_angl  > 0 && rays[i].ray_angl <  M_PI)
			rays[i].down = 1;
		rays[i].up =!rays->down;
		if(rays[i].ray_angl < 1.5 * M_PI &&  
			rays[i].ray_angl > 0.5 * M_PI )
			rays->left = 1;
		rays[i].right = !rays[i].left;
		angle_inc += FOV / num_rays;
		rays[i].ver_distance = 0;
		rays[i].Wall_hit_x = 0;
		rays[i].Wall_hit_y= 0;
		
		i++;
	}
}
void rander_ray(t_player *player, t_img *data,int map[10][10])
{
	t_rays *rays;
	int coulmn = 0;
	rays = malloc(sizeof(t_rays) * player->num_rays);
	init_rays(rays,player->num_rays,player->pa);
	int i = 0;
	while (i < player->num_rays)
	{
			
			printf("%f\n",rays[i].ray_angl);
			rays[i].ray_angl += FOV / player->num_rays;
			rays[i].ray_angl = normalize_angle(rays[i].ray_angl);
			casting(&rays[i],player,map);
			if(rays->found)
				draw_line(player->x,player->y,rays[i].Wall_hit_x ,rays[i].Wall_hit_y,data,0xff0000);
			draw_line(player->x,player->y,player->x + cos(player->pa) * 30 ,player->y + sin(player->pa) * 30,data,0x00fff00);
			i++;
			coulmn++;
			
	}
}
void	rander_player(t_player *player, t_img *data,int map[10][10])
{
	int	i, j;
	int	px = player->x - 3;
	int	py = player->y - 3;

	i = 0;
	while (i < 6)
	{
		j = 0;
		while (j < 6)
		{
			my_mlx_pixel_put(data, px + j, py + i, 0xFF000);
			j++;
		}
		i++;
	}
	rander_ray(player,data,map);
}



void draw(t_all_data *data)
{
  
    int         i, j;
    int         x0, y0;
    int         color;
    int         border = 0x000000;

    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < 10 )
        {
            x0 = j * TAIL;
            y0 = i * TAIL;
            if (data->map[i][j] == 1)
                color = 0xffffff;
            else
                color = 0x0000;

            for (int yy = 0; yy < TAIL; yy++)
            {
                for (int xx = 0; xx < TAIL; xx++)
                    my_mlx_pixel_put(&data->img, x0 + xx, y0 + yy, color);
            }
            draw_line(x0,y0,x0 + 31, y0,&data->img, border);
            draw_line(x0 + 31 ,y0,x0 + 31, y0 + 31,&data->img, border);
            draw_line(x0 + 31,y0 + 31,x0,y0 + 31,&data->img, border);
            draw_line(x0,y0 + 31,x0,y0,&data->img, border);

            j++;
        }
        i++;
    }
    rander_player(&data->player, &data->img,data->map);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img,0, 0);
}


void player_inite(t_player *player)
{
    player->x     = 160.0;
    player->y     = 160.0;
    player->pa    = M_PI * 2;
    player->speed = 5.0;
    player->pdx   = cos(player->pa) * player->speed;
    player->pdy   = sin(player->pa) * player->speed;
    player->num_rays = 320 / wall_strip;
}

int keys_press(int key_code, void *data_ptr)
{
    t_all_data *data = data_ptr;
    double newx = data->player.x;
    double newy = data->player.y;

    if (key_code == 13)      // W: forward
    {
        newx += data->player.pdx;
        newy += data->player.pdy;
    }
    else if (key_code == 1)  // S: backward
    {
        newx -= data->player.pdx;
        newy -= data->player.pdy;
    }
    else if (key_code == 0)  // A: turn left
    {
        data->player.pa -= 0.4;
        if (data->player.pa < 0)
            data->player.pa += 2 * M_PI;
        data->player.pdx = cos(data->player.pa) * data->player.speed;
        data->player.pdy = sin(data->player.pa) * data->player.speed;
    }
    else if (key_code == 2)  // D: turn right
    {
        data->player.pa += 0.4;
        if (data->player.pa > 2 * M_PI)
            data->player.pa -= 2 * M_PI;
        data->player.pdx = cos(data->player.pa) * data->player.speed;
        data->player.pdy = sin(data->player.pa) * data->player.speed;
    }
    if (!has_aw_wall((int)newx, (int)newy, data->map))
    {
        data->player.x = newx;
        data->player.y = newy;
    }

    draw(data);
    return 0;
}


int	main(void)
{
	t_img       img;
	t_player    player;
	t_all_data  data;
	int         map[10][10] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,0,1,0,1},
		{1,0,1,0,0,1,0,1,0,1},
		{1,0,1,0,0,1,0,1,0,1},
		{1,0,1,0,1,1,0,1,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,1},
		{1,0,1,1,0,1,0,1,0,1},
		{1,0,0,1,0,1,0,1,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	data.mlx     = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 10 * TAIL, 10 * TAIL, "raycasting");
	img.img = mlx_new_image(data.mlx, 10 * TAIL, 10 * TAIL);
	img.addr = mlx_get_data_addr(img.img,&img.bits_per_pixel,
	&img.line_length, &img.endian);
	data.img = img;
	player_inite(&player);
	data.player = player;
	memcpy(data.map, map, sizeof(map));
	mlx_key_hook(data.mlx_win,keys_press,&data);
	draw(&data);
	mlx_loop(data.mlx);
	return (0);
}
