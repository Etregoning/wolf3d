/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:18:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/05 19:01:02 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_forward(t_env *env)
{
	int	x;
	int	y;

	x = (int)(env->pos_x + env->dir_x * env->mov_speed);
	y = (int)(env->pos_y + env->dir_y * env->mov_speed);
	if (env->key_pressed->up && !env->key_pressed->down)
	{
		if (env->map->map_arr[x][y] == 0)
		{
			env->pos_x += env->dir_x * env->mov_speed;
			env->pos_y += env->dir_y * env->mov_speed;
		}
	}
}

void	move_backward(t_env *env)
{
	int	x;
	int	y;

	x = (int)(env->pos_x - env->dir_x * env->mov_speed);
	y = (int)(env->pos_y - env->dir_y * env->mov_speed);
	if (env->key_pressed->down && !env->key_pressed->up)
	{
		if (env->map->map_arr[x][y] == 0)
		{
			env->pos_x -= env->dir_x * env->mov_speed;
			env->pos_y -= env->dir_y * env->mov_speed;
		}
	}
}

void	rotate_left(t_env *env)
{
	if (env->key_pressed->left && !env->key_pressed->right)
	{
		env->old_dir_x = env->dir_x;
		env->dir_x = env->dir_x * cos(-(env->rot_speed)) - env->dir_y
						* sin(-(env->rot_speed));
		env->dir_y = env->old_dir_x * sin(-(env->rot_speed)) + env->dir_y
						* cos(-(env->rot_speed));
		env->old_plane_x = env->plane_x;
		env->plane_x = env->plane_x * cos(-(env->rot_speed)) - env->plane_y
						* sin(-(env->rot_speed));
		env->plane_y = env->old_plane_x * sin(-(env->rot_speed)) +
						env->plane_y * cos(-(env->rot_speed));
	}
}

void	rotate_right(t_env *env)
{
	if (env->key_pressed->right && !env->key_pressed->left)
	{
		env->old_dir_x = env->dir_x;
		env->dir_x = env->dir_x * cos(env->rot_speed) - env->dir_y
						* sin(env->rot_speed);
		env->dir_y = env->old_dir_x * sin(env->rot_speed) + env->dir_y
						* cos(env->rot_speed);
		env->old_plane_x = env->plane_x;
		env->plane_x = env->plane_x * cos(env->rot_speed) - env->plane_y
						* sin(env->rot_speed);
		env->plane_y = env->old_plane_x * sin(env->rot_speed) + env->plane_y
						* cos(env->rot_speed);
	}
}
