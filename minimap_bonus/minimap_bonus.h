/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:27:53 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/16 21:47:16 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
#define MINIMAP_BONUS_H

# include <mlx.h>
# include "../libft/libft.h"
# include "../raycasting/raycasting.h"


# define MINIMAP_H 100
# define MINIMAP_W 50

typedef struct s_mmap
{
	int	vidible_field;
	int	tile_size;
	void	*img_ptr
}	t_mmap;

#endif