/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:28:06 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/12 14:23:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raycasting.h"
typedef struct s_point
{
	int x;
	int y;
} t_point;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr
	    + (y * data->line_length
	    +  x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
void	rander_player(t_player *player, t_img *data)
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
	draw_line(player->x,player->y,player->x + player->pdx * 4 ,player->y + player->pdy * 4,data,0xff0000);
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
            x0 = j * 32;
            y0 = i * 32;
            if (data->map[i][j] == 1)
                color = 0xffffff;
            else
                color = 0x0000;

            for (int yy = 0; yy < 32; yy++)
            {
                for (int xx = 0; xx < 32; xx++)
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
    rander_player(&data->player, &data->img);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img,0, 0);
}


void	player_inite(t_player *player)
{
	player->x = 160;
	player->y = 160;
	player->pdx = cos(player->pa)*5 ;
	player->pdy = sin(player->pa) * 5;
	player->pa = M_PI;
}

int	keys_press(int key_code, void *data_ptr)
{
	t_all_data *data = (t_all_data *)data_ptr;

	if (key_code == 13)
	{
		data->player.y += data->player.pdy *2;
		data->player.x += data->player.pdx * 2;
	}
	else if (key_code == 1)
	{
		data->player.y -= data->player.pdy *2;
		data->player.x -= data->player.pdx *2;
	}
	else if (key_code == 0)
	{
		data->player.pa -= 0.4;
		if(data->player.pa < 0)
			data->player.pa+= 2 * M_PI;
		data->player.pdx = cos(data->player.pa)*5;
		data->player.pdy = sin(data->player.pa)*5;
	}
	else if (key_code == 2)
	{
		data->player.pa += 0.4;
		if(data->player.pa > 0)
			data->player.pa-= 2 * M_PI;
		data->player.pdx = cos(data->player.pa)*5;
		data->player.pdy = sin(data->player.pa)*5;
	}
	draw(data);
	return (0);
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
	data.mlx_win = mlx_new_window(data.mlx, 10 * 32, 10 * 32, "raycasting");

	img.img = mlx_new_image(data.mlx, 10 * 32, 10 * 32);
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
