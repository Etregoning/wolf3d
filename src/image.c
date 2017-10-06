/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:57:29 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/05 18:52:10 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		put_line_to_img(t_env *env, int x, int y1, int y2)
{
	int	y;

	y = -1;
	if (y1 < 0)
		y1 = 0;
	if (y2 > env->height)
		y2 = env->height - 1;
	while (++y <= y1)
		env->img_addr[x + (y * env->size_line / 4)] = 0x222222;
	while (++y <= y2)
	{
		if (env->wall_color_toggle == 0)
			env->img_addr[x + (y * env->size_line / 4)] = get_wall_color(env);
		else if (env->wall_color_toggle == 1)
			env->img_addr[x + (y * env->size_line / 4)] =
				wall_color_toggled(env);
		if (env->map->map_arr[env->map_x][env->map_y] == 2)
			env->img_addr[x + (y * env->size_line / 4)] = 0xffa500;
	}
	while (++y < 1200)
		env->img_addr[x + (y * env->size_line / 4)] = env->floor_color;
	return (0);
}

void	create_image(t_env *env)
{
	env->img_h = env->height;
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->img_addr = (int*)mlx_get_data_addr(env->img,
					&(env->bits_per_pixel), &(env->size_line), &(env->endian));
	env->floor = mlx_xpm_file_to_image(env->mlx, "./xpm/floor.xpm",
					&(env->width), &(env->img_h));
}
