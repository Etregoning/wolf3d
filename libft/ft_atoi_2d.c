/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 18:08:42 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/30 18:13:39 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_atoi_2d(char **s, int w)
{
	int *map;
	int i;

	i = 0;
	map = (int *)malloc(sizeof(int) * (w + 1));
	while (i < w)
	{
		map[i] = ft_atoi(&s[i][0]);
		i++;
	}
	return (map);
}
