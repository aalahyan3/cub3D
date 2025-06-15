/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:11:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/15 14:54:04 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

void clear_map(t_map *map)
{
	free(map->n_path);
	free(map->s_path);
	free(map->w_path);
	free(map->e_path);
	free_2d_array(map->arr);
	free(map);
}