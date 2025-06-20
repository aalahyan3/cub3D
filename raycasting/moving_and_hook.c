/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_and_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/06/20 17:04:23 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raycasting.h"

void	rotate_player(t_player *p, t_keys k)
{
	if (k.left)
		p->pa -= ROTATION_SPEED;
	if (k.right)
		p->pa += ROTATION_SPEED;
	if (p->pa < 0)
		p->pa += 2 * M_PI;
	if (p->pa > 2 * M_PI)
		p->pa -= 2 * M_PI;
	p->pdx = cos(p->pa) * p->speed;
	p->pdy = sin(p->pa) * p->speed;
}

void	move_player(t_all_data *d, double *nx, double *ny)
{
	t_keys	k;

	k = d->keys;
	if (k.w)
	{
		*nx += d->player.pdx;
		*ny += d->player.pdy;
	}
	if (k.s)
	{
		*nx -= d->player.pdx;
		*ny -= d->player.pdy;
	}
	if (k.a)
	{
		*nx += d->player.pdy;
		*ny -= d->player.pdx;
	}
	if (k.d)
	{
		*nx -= d->player.pdy;
		*ny += d->player.pdx;
	}
}


int	handle_keys(void *param)
{
	double	nx;
	double	ny;
	void	*minimap;
	void	*frame;
	static int	frame_delta[2] = {0, 10};
	static int	increaments[2] = {1, 1};
	static int	frame_stop = 0;
	t_all_data	*d;
	d = (t_all_data *)param;
	mlx_clear_window(d->mlx, d->mlx_win);
	rotate_player(&d->player, d->keys);
	nx = d->player.x;
	ny = d->player.y;
	move_player(d, &nx, &ny);
	if (!has_wall_with_radius((int)nx, (int)ny,RADIUS, d->map))
	{
		d->player.x = nx;
		d->player.y = ny;
	}
	draw(d);
	minimap = get_minimap(d);
	frame = get_animation_frame(d);
	if (d->keys.space)
	{
			d->player.shot = 1;
	}
	if (frame_delta[0] == 10)
		increaments[0] = -1;
	else if (frame_delta[0] == 0)
		increaments[0] = 1;
	if (frame_delta[1] == 10)
		increaments[1] = -2;
	else if (frame_delta[1] == 0)
		increaments[1] = 2;
	if (frame_stop >= 5)
	{
		frame_delta[0] += increaments[0];
		frame_delta[1] += increaments[1];
		frame_stop = 0;
	}
	else
		frame_stop++;

	mlx_put_image_to_window(d->mlx, d->mlx_win, frame, WIN_WIDTH / 2 + 80 + frame_delta[0], WIN_HEIGHT - 160 + frame_delta[0]);
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->crosshair.img, WIN_WIDTH / 2 - 25, WIN_HEIGHT / 2 - 25);
	mlx_put_image_to_window(d->mlx, d->mlx_win, minimap, 0, 0);
	mlx_destroy_image(d->mlx, minimap);
	return (0);
}

int	key_press(int keycode, void *param)
{

	t_all_data *data = (t_all_data *)param;
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
	if (keycode == 49)
		data->keys.space = 1;
	if (keycode == 125)
		data->keys.down = 1;
	if (keycode == 126)
		data->keys.up = 1;
	if (keycode == 53)
		cleanup(data);
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
	// if (keycode == 49)
	// 	data->keys.right = 0;
	return (0);
}
