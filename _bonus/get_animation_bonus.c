/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:30:57 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/21 15:41:33 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_bonus.h"

void	*get_animation_frame(t_all_data *data)
{
	static int	frame_counter = 0;
	static int	show_counter = 0;
	int			stop_at;

	stop_at = 5;
	if (data->player.shot == 0)
		return (data->frames[0].img);
	if (show_counter >= stop_at)
	{
		frame_counter++;
		show_counter = 0;
		if (frame_counter >= 3)
		{
			frame_counter = 0;
			data->player.shot = 0;
			data->keys.space = 0;
			return (data->frames[0].img);
		}
	}
	else
		show_counter++;
	return (data->frames[frame_counter].img);
}
