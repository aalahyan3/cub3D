/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:29:44 by aalahyan          #+#    #+#             */
/*   Updated: 2025/06/21 14:21:36 by aalahyan         ###   ########.fr       */
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

int	atoi_for_rgb(char *s, char *line)
{
	int	res;
	int	i;
	int	digits;

	res = 0;
	i = 0;
	if (! s || !*s)
		return (ft_putstr_fd("Error\nnon valid rgb value in : ", 2), \
		ft_putstr_fd(line, 2), -1);
	digits = 0;
	while (s[i] && s[i] == '0')
		i++;
	while (ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		i++;
		digits++;
	}
	if (digits > 3 || res > 255)
	{
		ft_putstr_fd("Error\nnon valid rgb value in : ", 2);
		ft_putstr_fd(line, 2);
		return (-1);
	}
	return (res);
}
