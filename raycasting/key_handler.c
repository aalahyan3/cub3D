/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:42:00 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/23 15:48:11 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	key_press(int keycode, void *param)
{
	t_all_data	*data;

	data = (t_all_data *)param;
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
		cleanup(data, 0);
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
