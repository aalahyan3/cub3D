/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:06:58 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/19 19:24:46 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mouse_handler.h"

int	mouse_handler(int x, int y, void *param)
{
	t_all_data	*data;
	int	dx;


	data = (t_all_data *)param;
	if (data->cursor_x == -1)
	{
		data->cursor_x = x;
		return (0);
	}
	if (data->keys.left || data->keys.right)
		return 0;
	dx = data->cursor_x - x;
	// ft_printf("%d\n", dx);
	data->player.pa -= dx * 0.005;
	data->cursor_x = x;
	return (0);
}