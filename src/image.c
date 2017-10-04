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
		if (env->side_hit == 1)
			env->img_addr[x + (y * env->size_line / 4)] = 0x8b0000;
		else
			env->img_addr[x + (y * env->size_line / 4)] = 0xFF0000;
  	}
	while (++y < 1190)
		env->img_addr[x + (y * env->size_line / 4)] = 0x7e7e7e;
  return (0);
}

void	create_image(t_env *env)
{
	env->img_h =  env->height;
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->img_addr = (int*)mlx_get_data_addr(env->img,
					&(env->bits_per_pixel), &(env->size_line), &(env->endian));
	env->floor = mlx_xpm_file_to_image(env->mlx, "./xpm/floor.xpm",
					&(env->width), &(env->img_h));



}
