/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:37:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 20:09:33 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_map(t_map *map, int *helper_infos)
{
	map->arr = NULL;
	map->e_path = NULL;
	map->n_path = NULL;
	map->s_path = NULL;
	map->w_path = NULL;
	ft_bzero(helper_infos, 3 * sizeof(int));
}

void	fill_map_data(t_map *map, int fd)
{
	char	*line;
	int		helper_infos[3];

	1 && (init_map(map, helper_infos), line = get_next_line(fd));
	while (line)
	{
		if (*line != '0' && *line != '1' && *line != ' ' && *line != '\n')
		{
			if (!set_attribute(map, line, helper_infos))
				exit_error(map, line, fd);
			helper_infos[0] += 1;
		}
		else if (*line == '1' || *line == ' ' || *line == '0')
		{
			if (helper_infos[0] != 6)
			{
				ft_putstr_fd("Error\nthe map was \
				found before all data provided.\n", 2);
				exit_error(map, line, fd);
			}
			start_map_reading(map, line, fd);
			break ;
		}
		1 && (free(line), line = get_next_line(fd));
	}
}
