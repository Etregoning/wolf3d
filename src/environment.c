/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:49:07 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/05 18:48:15 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	redraw(t_env *env)
{
	env->expose = 0;
	create_image(env);
	game_loop(env);
	mlx_put_image_to_window(env->mlx, env->win, env->floor, 0, 600);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if ((int)env->pos_x == 1 && (int)env->pos_y == 7)
	{
		mlx_string_put(env->mlx, env->win, 600, 600, 0x000000, "You win!!");
		mlx_string_put(env->mlx, env->win, 450, 630, 0x000000,
						"Press Esc to exit, or space to play again!");
	}
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_image(env->mlx, env->floor);
}

void	environment_init(t_env *env)
{
	env->expose = 1;
	env->width = 1200;
	env->height = 1200;
	env->pos_x = 1.25;
	env->pos_y = 3.5;
	env->dir_x = 1.0;
	env->dir_y = 0.0;
	env->plane_x = 0;
	env->plane_y = 0.66;
	env->rot_speed = 0.040;
	env->mov_speed = 0.050;
	env->floor_color = 0x7e7e7e;
	env->key_pressed->up = 0;
	env->key_pressed->down = 0;
	env->key_pressed->left = 0;
	env->key_pressed->right = 0;
	env->wall_color_toggle = 0;
}

void	set_hooks(t_env *env)
{
	mlx_hook(env->win, 2, 0, pressed_hook, env);
	mlx_hook(env->win, 3, 0, released_hook, env);
	mlx_hook(env->win, 17, 0, exit_hook, env);
}

void	make_environment(void *mlx, t_env *env)
{
	if (!(env->ray = (t_ray*)ft_memalloc(sizeof(t_ray))))
		ft_error("Error: Failed to allocate memory line 63 environment.c");
	if (!(env->key_pressed = (t_keys*)ft_memalloc(sizeof(t_keys))))
		ft_error("Error: Failed to allocate memory line 65 environment.c");
	env->mlx = mlx;
	environment_init(env);
}
