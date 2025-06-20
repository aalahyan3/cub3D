/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:29:44 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/20 20:27:52 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*path_skipper(char *path)
{
	while (*path && *path != ' ')
		path++;
	while (*path && *path == ' ')
		path++;
	return (path);
}

void	exit_error(t_map *map, char *line, int fd)
{
	close(fd);
	clear_map(map);
	free(line);
	exit(1);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}
