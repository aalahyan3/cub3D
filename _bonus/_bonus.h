/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:11 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/22 14:20:44 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BONUS_H
# define _BONUS_H

# include <mlx.h>
# include "../raycasting/all_data_struct.h"
# include "../libft/libft.h"

typedef struct s_minimap
{
	t_img	*image;
	int		width;
	int		height;
	int		view_range;
	int		tile_size;
}	t_minimap;

void	*get_minimap(t_all_data *data);
void	*get_animation_frame(t_all_data *data);
int		mouse_handler(int x, int y, void *param);

#endif