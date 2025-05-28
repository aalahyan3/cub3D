/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_and_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:34:47 by zkhourba          #+#    #+#             */
/*   Updated: 2025/05/28 16:36:07 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void rotate_player(t_player *p, t_keys k)
{
    if (k.left)
        p->pa -= 0.02;
    if (k.right)
        p->pa += 0.02;
    if (p->pa < 0)
        p->pa += 2 * M_PI;
    if (p->pa > 2 * M_PI)
        p->pa -= 2 * M_PI;
    p->pdx = cos(p->pa) * p->speed;
    p->pdy = sin(p->pa) * p->speed;
}

void move_player(t_all_data *d, double *nx, double *ny)
{
    t_keys k = d->keys;
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

int handle_keys(t_all_data *d)
{
    double nx;
    double ny;

    rotate_player(&d->player, d->keys);
    nx = d->player.x;
    ny = d->player.y;
    move_player(d, &nx, &ny);
    if (!has_aw_wall((int)nx, (int)ny, d->map))
    {
        d->player.x = nx;
        d->player.y = ny;
    }
    draw(d);
    return (0);
}

int key_press(int keycode, t_all_data *data)
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

int key_release(int keycode, t_all_data *data)
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