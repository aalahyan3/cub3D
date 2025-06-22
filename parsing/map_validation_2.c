/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhourba <zkhourba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:13:52 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/22 15:18:55 by zkhourba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	valid_wall(char **arr, int i, int j)
{
	if ((i == 0 || j == 0 || !arr[i + 1] || !arr[i][j + 1]) \
	&& (arr[i][j] != ' ' && arr[i][j] != '1'))
	{
		ft_putstr_fd("Error\nthe arr must be surrounded by wall1\n", 2);
		return (false);
	}
	if (arr[i][j] == ' ')
	{
		if ((arr[i][j + 1] && (arr[i][j + 1] != '1' && arr[i][j + 1] != ' ' )) \
		|| (j != 0 && (arr[i][j - 1] != '1' && arr[i][j - 1] != ' ')) \
		|| (arr[i + 1] && (arr[i + 1][j] != '1' && arr[i + 1][j] != ' ')) \
		|| (i != 0 && (arr[i - 1][j] != '1' && arr[i - 1][j] != ' ')))
		{
			ft_putstr_fd("Error\nthe map must be surrounded by wall\n", 2);
			return (false);
		}
	}
	return (true);
}

static void	setup_player(t_map *map, char **arr, int i, int j)
{
	map->px = j;
	map->py = i;
	if (arr[i][j] == 'S')
		map->i_angle = M_PI_2;
	else if (arr[i][j] == 'N')
		map->i_angle = 3 * M_PI_2;
	else if (arr[i][j] == 'W')
		map->i_angle = M_PI;
	else if (arr[i][j] == 'E')
		map->i_angle = 0.0;
}

bool	surrounded_by_walls(char **map, t_map *map_s)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!valid_wall(map, i, j))
				return (false);
			if (ft_isalpha(map[i][j]))
				setup_player(map_s, map, i, j);
			j++;
		}
		i++;
	}
	map_s->map_w = j;
	map_s->map_h = i;
	return (true);
}

static int	get_longest_row(char **map)
{
	int	longest;
	int	i;

	i = 0;
	longest = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	return (longest);
}

void	adjust_map_structure(char **map)
{
	int		longest;
	int		i;
	char	*new;
	int		j;

	1 && (longest = get_longest_row(map), i = 0);
	while (map[i])
	{
		if (ft_strlen(map[i]) < longest)
		{
			j = 0;
			new = malloc(sizeof(char) * (longest + 1));
			if (!new)
				return ;
			while (j < ft_strlen(map[i]))
				1 && (new[j] = map[i][j], j = j + 1);
			while (j < longest)
				new[j++] = ' ';
			new[j] = 0;
			free(map[i]);
			map[i] = new;
		}
		i++;
	}
}
