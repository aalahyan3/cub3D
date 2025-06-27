/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_and_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:40:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/27 10:44:13 by aalahyan         ###   ########.fr       */
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

void	draw_animation(t_all_data *data)
{
	static int	frame_delta[2] = {0, 10};
	static int	increaments[2] = {1, 1};
	static int	frame_counter = 0;
	void		*frame;

	if (frame_delta[0] == 10)
		increaments[0] = -1;
	else if (frame_delta[0] == 0)
		increaments[0] = 1;
	if (frame_delta[1] == 10)
		increaments[1] = -2;
	else if (frame_delta[1] == 0)
		increaments[1] = 2;
	if (frame_counter >= 5)
		1 && (frame_delta[0] += increaments[0], \
		frame_delta[1] += increaments[1], frame_counter = 0);
	else
		frame_counter++;
	if (data->keys.space)
		data->player.shot = 1;
	frame = get_animation_frame(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, frame, \
	WIN_WIDTH / 2 + 80 + frame_delta[0], \
WIN_HEIGHT - 160 + frame_delta[0]);
}

int	handle_keys(void *param)
{
	double		nx;
	double		ny;
	void		*minimap;
	t_all_data	*d;

	d = (t_all_data *)param;
	mlx_clear_window(d->mlx, d->mlx_win);
	rotate_player(&d->player, d->keys);
	nx = d->player.x;
	ny = d->player.y;
	move_player(d, &nx, &ny);
	if (!has_wall_with_radius((int)nx, (int)ny, RADIUS, d->map))
	{
		d->player.x = nx;
		d->player.y = ny;
	}
	draw(d);
	draw_animation(d);
	minimap = get_minimap(d);
	mlx_put_image_to_window(d->mlx, d->mlx_win, d->crosshair.img,
		WIN_WIDTH / 2 - 25,
		WIN_HEIGHT / 2 - 25);
	mlx_put_image_to_window(d->mlx, d->mlx_win, minimap, 0, 0);
	mlx_destroy_image(d->mlx, minimap);
	return (0);
}
