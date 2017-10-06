/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 13:47:37 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/05 18:47:25 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				floor_toggle(t_env *env)
{
	if (env->floor_color == 0x7e7e7e)
		env->floor_color = 0xffffffff;
	else if (env->floor_color == 0xffffffff)
		env->floor_color = 0x7e7e7e;
	released_hook(KEY_F, env);
	return (0);
}

unsigned int	get_wall_color(t_env *env)
{
	unsigned int	wall_color;

	if (env->ray->dir_x < 0)
	{
		if (env->side_hit == 1)
			wall_color = 0xff0000;
		else
			wall_color = 0x8b0000;
	}
	else
	{
		if (env->side_hit == 1)
			wall_color = 0xff0000;
		else
			wall_color = 0x8b0000;
	}
	return (wall_color);
}

unsigned int	wall_color_toggled(t_env *env)
{
	unsigned int wall_color;

	if (env->ray->dir_y < 0 && env->side_hit == 1)
		wall_color = 0x00ff00;
	else if (env->ray->dir_x < 0 && env->side_hit == 0)
		wall_color = 0x0000ff;
	else if (env->side_hit == 1)
		wall_color = 0xffff00;
	else
		wall_color = 0xff0000;
	return (wall_color);
}
