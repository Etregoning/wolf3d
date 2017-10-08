/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:17:06 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 18:39:15 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	check_line(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		ft_error("Error: Line not read.");
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1)
			ft_error("Error: Alphabetical characters found.");
		if ((str[i] == '-' && !(ft_isdigit(str[i + 1]))) || str[i] == '\t')
			ft_error("Error: Forbidden characters found.");
		i++;
	}
}

int		count_width(char *map_coord)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_coord[i] != '\0')
	{
		if (map_coord[i] != ' ')
		{
			j++;
			while ((map_coord[i] != ' ') && (map_coord[i] != '\0'))
				++i;
		}
		else
			++i;
	}
	return (j);
}

void	get_map_width(t_env *env, int fd)
{
	int		width;
	char	**points;
	int		j;
	
	j = 0;
	if (get_next_line(fd, &(env->map->line)))
	{
		points = ft_strsplit(env->map->line, ' ');
		check_line(env->map->line);
		width = count_width(env->map->line);
		free(env->map->line);
		if (width < 2)
			ft_error("Error: Map is not wide enough.");
		else
		{
			env->map->width = width;
		}
		while (points[j])
		{
			free(points[j]);
			j++;
		}
		free(points);
	}
	else
		ft_error("Error: Empty map");
}

void	get_map_height(t_env *env, int fd)
{
	int		width;
	int		i;
	int		j;
	char	**points;

	i = 1;
	while (get_next_line(fd, &(env->map->line)))
	{
		points = ft_strsplit(env->map->line, ' ');
		check_line(env->map->line);
		width = count_width(env->map->line);
		free(env->map->line);
		if (width != env->map->width)
			ft_error("Error: Width uneven.");
		j = 0;
		while (points[j])
		{
			free(points[j]);
			j++;
		}
		free(points);
		i++;
	}
	env->map->height = i;
	close(fd);
}

void	store_map(t_env *env, int fd)
{
	int		i;
	int		j;
	char	**points;

	i = 0;
	env->map->map_arr = (int **)malloc(sizeof(int *) * (env->map->height + 1));
	while (get_next_line(fd, &(env->map->line)) > 0)
	{
		points = ft_strsplit(env->map->line, ' ');
		free(env->map->line);
		env->map->map_arr[i] = ft_atoi_2d(points, env->map->width);
		j = 0;
		while (points[j])
		{
			free(points[j]);
			j++;
		}
		free(points);
		i++;
	}
	close(fd);
}
