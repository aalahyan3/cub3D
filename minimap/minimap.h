/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:56:11 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 15:52:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include <mlx.h>
#include "../raycasting/all_data_struct.h"
#include "../libft/libft.h"
typedef struct s_minimap
{
	t_img	*image;
	int	width;
	int	height;
	int	view_range;
	int	tile_size;
}	t_minimap;

void	*get_minimap(t_all_data *data);


#endif