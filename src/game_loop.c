/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:21:08 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 17:13:05 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	calc_ray(t_env *env, int i)
{
	env->cam_x = 2 * i / (double)env->width - 1;
	env->ray->pos_x = env->pos_x;
	env->ray->pos_y = env->pos_y;
	env->ray->dir_x = env->dir_x + env->plane_x * env->cam_x;
	env->ray->dir_y = env->dir_y + env->plane_y * env->cam_x;
	env->map_x = (int)env->ray->pos_x;
	env->map_y = (int)env->ray->pos_y;
	env->ray->delta_x = sqrt(1 + (env->ray->dir_y * env->ray->dir_y) /
						(env->ray->dir_x * env->ray->dir_x));
	env->ray->delta_y = sqrt(1 + (env->ray->dir_x * env->ray->dir_x) /
						(env->ray->dir_y * env->ray->dir_y));
	env->hit = 0;

}

void	calc_step(t_env *env)
{
	if (env->ray->dir_x < 0)
	{
		env->step_x = -1;
		env->ray->side_x = (env->ray->pos_x - env->map_x)
							* env->ray->delta_x;
	}
	else
	{
		env->step_x = 1;
		env->ray->side_x = (env->map_x + 1.0 - env->ray->pos_x)
							* env->ray->delta_x;
	}
	if (env->ray->dir_y < 0)
	{
		env->step_y = -1;
		env->ray->side_y = (env->ray->pos_y - env->map_y)
							* env->ray->delta_y;
	}
	else
	{
		env->step_y = 1;
		env->ray->side_y = (env->map_y + 1.0 - env->ray->pos_y)
							* env->ray->delta_y;
	}

}

void	dda_start(t_env *env)
{
	while (env->hit == 0)
	{

		if (env->ray->side_x < env->ray->side_y)
		{
			env->ray->side_x += env->ray->delta_x;
			env->map_x += env->step_x;
			env->side_hit = 0;
		}
		else
		{
			env->ray->side_y += env->ray->delta_y;
			env->map_y += env->step_y;
			env->side_hit = 1;
		}
		if (env->map->map_arr[env->map_x][env->map_y] > 0)
			env->hit = 1;
	}

}

void	calc_fov(t_env *env)
{
	if (env->side_hit == 0)
		env->ray->wall_dist = (env->map_x - env->ray->pos_x +
								(1 - env->step_x) / 2) / env->ray->dir_x;
	else
		env->ray->wall_dist = (env->map_y - env->ray->pos_y +
								(1 - env->step_y) / 2) / env->ray->dir_y;
	env->ray->line_height = (int)(env->height / env->ray->wall_dist);
	env->ray->draw_start = -env->ray->line_height / 2 + env->height / 2;
	if(env->ray->draw_start < 0)
		env->ray->draw_start = 0;
	env->ray->draw_end = env->ray->line_height / 2 + env->height / 2;
	if(env->ray->draw_end >= env->height)
		env->ray->draw_end = env->height - 1;
}
/*
void	game_loop(void *current_thread)
{
	t_env		*env;
	t_thread	*t;
	int			x;

	x = 0;
	t = (t_thread*)current_thread;
	env = t->env;
	while (x++ < env->width)
	{
			calc_ray(env, x);
			calc_step(env);
			dda_start(env);
			calc_fov(env);
			put_line_to_img(env, t, env->ray->draw_start, env->ray->draw_end);
	}
}
*/

void	game_loop(t_env *env)
{
	int x;

	x = 0;
	while (x++ < env->width)
	{
			calc_ray(env, x);
			calc_step(env);
			dda_start(env);
			calc_fov(env);
			put_line_to_img(env, x, env->ray->draw_start, env->ray->draw_end);
	}
}
