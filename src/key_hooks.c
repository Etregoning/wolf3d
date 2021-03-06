/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:52:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 19:32:52 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		exit_hook(t_env *env)
{
	int i;

	i = 0;
	mlx_destroy_window(env->mlx, env->win);
	free(env->ray);
	free(env->key_pressed);
	while (i < env->map->width)
		free(env->map->map_arr[i++]);
	free(env->map->map_arr);
	free(env->map);
	free(env->img);
	free(env);
	exit(0);
	return (0);
}

int		pressed_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		exit_hook(env);
	toggle_keys(keycode, env, 1);
	return (0);
}

int		released_hook(int keycode, t_env *env)
{
	toggle_keys(keycode, env, 0);
	env->expose = 1;
	return (0);
}

void	toggle_keys(int keycode, t_env *env, int toggle)
{
	if (keycode == KEY_UP)
		env->key_pressed->up = toggle;
	if (keycode == KEY_DOWN)
		env->key_pressed->down = toggle;
	if (keycode == KEY_LEFT)
		env->key_pressed->left = toggle;
	if (keycode == KEY_RIGHT)
		env->key_pressed->right = toggle;
	if (keycode == KEY_F)
		env->key_pressed->f = toggle;
	if (keycode == KEY_C)
		env->key_pressed->c = toggle;
	if (keycode == KEY_SPACE)
		env->key_pressed->space = toggle;
}

int		loop_hook(t_env *env)
{
	if (env->key_pressed->up || env->key_pressed->down ||
		env->key_pressed->left || env->key_pressed->right)
		env->expose = 1;
	if (env->key_pressed->up)
		move_forward(env);
	if (env->key_pressed->down)
		move_backward(env);
	if (env->key_pressed->right)
		rotate_right(env);
	if (env->key_pressed->left)
		rotate_left(env);
	if (env->key_pressed->f)
		floor_toggle(env);
	if (env->key_pressed->c)
		wall_toggle(env);
	if (env->key_pressed->space)
		space_hook(env);
	if ((int)env->pos_x == 1 && env->pos_y < 4)
		close_doors(env);
	if (env->expose)
		redraw(env);
	return (0);
}
