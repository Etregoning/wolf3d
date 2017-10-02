/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:57:29 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/26 18:00:23 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			put_pixel_to_img(t_env *env, int x, int y, int color)
{
	int i;

	i = (x * (env->bits_per_pixel / 8)) + (y * env->size_line);
	if (env->side_hit == 1)
		color = 0x8b0000;
	if (x > 0 && y > 0 && x < env->width && y < env->height)
	{
		env->img_addr[i] = color;
		env->img_addr[++i] = color >> 8;
		env->img_addr[++i] = color >> 16;
	}
	else
		env->img_addr[i] = (char)env->floor;

}

int put_line_to_img(t_env *env, int x, int y1, int y2)
{
	if(y2 < y1)
	{
  		y1 += y2;
  		y2 = y1 - y2;
  		y1 -= y2;
	}
	if(y2 < 0 || y1 >= env->height  || x < 0 || x >= env->width)
		return (0);
	if(y1 < 0)
		y1 = 0;
	if(y2 >= env->width)
		y2 = env->height - 1;

 	while (y1++ <= y2)
  	{
	  put_pixel_to_img(env, x, y1, env->ray->wall_color);
  	}
  return (0);
}



int draw_background(t_env *env)
{
	int x;
	int	y;

	y = -1;

 	while (y++ < env->height)
  	{
		x = -1;
		while (x++ < env->width)
		{
			if (y < env->height / 2)
	  			put_pixel_to_img(env, x, y, 0xBDBDBD);
			else
				put_pixel_to_img(env, x, y, 0x7e7e7e);
		}
  	}
  return (0);
}

void	create_image(t_env *env)
{
	env->mid_y =  env->height / 2;
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->img_addr = mlx_get_data_addr(env->img,
					&(env->bits_per_pixel), &(env->size_line), &(env->endian));
	env->floor = mlx_xpm_file_to_image(env->mlx, "./xpm/floor_texture.xpm",
					&(env->width), &(env->mid_y));
	env->floor_addr =  mlx_get_data_addr(env->floor, &(env->bits_per_pixel),
						&(env->size_line), &(env->endian));
}
