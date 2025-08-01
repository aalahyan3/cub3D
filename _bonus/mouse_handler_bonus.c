/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:58 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/27 10:52:14 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_bonus.h"

int	mouse_handler(int x, int y, void *param)
{
	t_all_data	*data;
	int			dx;

	data = (t_all_data *)param;
	(void)y;
	if (data->cursor_x == -1)
	{
		data->cursor_x = x;
		return (0);
	}
	if (data->keys.left || data->keys.right)
		return (0);
	dx = data->cursor_x - x;
	data->player.pa -= dx * 0.005;
	data->cursor_x = x;
	return (0);
}
