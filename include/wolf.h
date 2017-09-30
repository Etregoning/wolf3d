/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:57:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 17:13:16 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# define NUM_THREADS 16

typedef struct	s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	double		wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			img_x;
	int			wall_color;
}				t_ray;

typedef struct	s_map
{
	int			**map_arr;
	char		*line;
	int			height;
	int			width;

}				t_map;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		prev_time;
	double		cam_x;
	double		mov_speed;
	double		rot_speed;
	int			expose;
	int			x;
	int			y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side_hit;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	t_ray		*ray;
	t_map		*map;
}				t_env;

typedef struct	s_thread
{
	t_env		*env;
	int			count;
	int			index;
	int			x;
	int			y;
}				t_thread;

int				world_map[24][24];
void			get_map_width(t_map *map, int fd);
void			get_map_height(t_map *map, int fd);
void			store_map(t_map *map, int fd);
int				*convert_to_int(char **s, int w);
t_env			*make_environment(void *mlx);
void			redraw(t_env *env);
int				loop_hook(t_env *env);
void			game_loop(t_env *env);
void			create_image(t_env *env);
void			init_thread(t_env *env);
void			put_pixel_to_img(t_env *env, int x, int y, int color);
int 			put_line_to_img(t_env *env, int x, int y1, int y2);

#endif
