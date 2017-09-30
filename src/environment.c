/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:49:07 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 17:13:14 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	redraw(t_env *env)
{
	env->expose = 0;
	mlx_clear_window(env->mlx, env->win);
	ft_bzero(env->img_addr, sizeof(env->img_addr));
	game_loop(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

void	environment_init(t_env *env)
{
	env->expose = 1;
	env->width = 1200;
	env->height = 1200;
	env->pos_x = 22;
	env->pos_y = 12;
	env->dir_x = -1;
	env->dir_y = 0;
	env->plane_x = 0;
	env->plane_y = 0.66;
	env->ray->wall_color = 0xFF0000;
}

t_env	*make_environment(void *mlx)
{
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	env->ray = (t_ray*)malloc(sizeof(t_ray));
	env->mlx = mlx;
	environment_init(env);
	return (env);
}
