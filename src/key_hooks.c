/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 18:52:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 18:52:50 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		exit_hook(t_env *env)
{
	mlx_destroy_window(env->mlx, env->win);
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
}

int	loop_hook(t_env *env)
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
	if (env->expose)
		redraw(env);
	return (0);
}
