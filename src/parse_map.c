/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:17:06 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/29 15:17:14 by etregoni         ###   ########.fr       */
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

int	count_width(char *map_coord)
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
				i++;
		}
		else
			i++;
	}
	return (j);
}

void	get_map_width(t_map *map, int fd)
{
	int		width;
	char	**points;

	if (get_next_line(fd, &(map->line)))
	{
		check_line(map->line);
		width = count_width(map->line);
		if (width < 2)
			ft_error("Error: Map is not wide enough.");
		else
		{
			points = ft_strsplit(map->line, ' ');
			map->width = width;
		}
	}
	else
		ft_error("Error: Empty map");
}

void	get_map_height(t_map *map, int fd)
{
	int	width;
	int	i;
	char	**points;

	i = 1;
	while (get_next_line(fd, &(map->line)))
	{
		check_line(map->line);
		width = count_width(map->line);
		if (width != map->width)
			ft_error("Error: Width uneven.");
		else
			points = ft_strsplit(map->line, ' ');
		i++;
	}
	map->height = i;
	free(map->line);
	free(points);
	close(fd);
}

void	store_map(t_map *map, int fd)
{
	int		i;
	char	**points;

	i = 0;
	map->map_arr = (int **)malloc(sizeof(int *) * (map->height + 1));
	while (get_next_line(fd, &(map->line)) > 0)
	{
		points = ft_strsplit(map->line, ' ');
		map->map_arr[i] = convert_to_int(points, map->width);
		i++;
	}
	free(map->line);
	free(points);
	close(fd);
}
