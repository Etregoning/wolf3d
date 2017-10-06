/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 18:30:27 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/05 18:54:36 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		wall_toggle(t_env *env)
{
	if (env->wall_color_toggle == 0)
		env->wall_color_toggle = 1;
	else if (env->wall_color_toggle == 1)
		env->wall_color_toggle = 0;
	released_hook(KEY_C, env);
	return (0);
}

int		space_hook(t_env *env)
{
	if ((int)env->pos_x == 1 && (int)env->pos_y == 7)
	{
		env->map->map_arr[1][5] = 0;
		env->map->map_arr[1][6] = 0;
	}
	released_hook(KEY_SPACE, env);
	return (0);
}

void	close_doors(t_env *env)
{
	env->map->map_arr[1][5] = 3;
	env->map->map_arr[1][6] = 2;
}
