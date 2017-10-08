/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:57:47 by etregoni          #+#    #+#             */
/*   Updated: 2017/10/07 18:34:16 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# define NUM_THREADS 16
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49
# define KEY_F 3
# define KEY_C 8

typedef	struct		s_keys
{
	int				f:1;
	int				c:1;
	int				up:1;
	int				down:1;
	int				left:1;
	int				right:1;
	int				space:1;
}					t_keys;

typedef struct		s_ray
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				img_x;
}					t_ray;

typedef struct		s_map
{
	int				**map_arr;
	char			*line;
	int				height;
	int				width;

}					t_map;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*floor;
	int				*img_addr;
	double			pos_x;
	double			pos_y;
	double			old_dir_x;
	double			dir_x;
	double			dir_y;
	double			old_plane_x;
	double			plane_x;
	double			plane_y;
	double			cam_x;
	double			mov_speed;
	double			rot_speed;
	unsigned int	floor_color;
	int				wall_color_toggle;
	int				img_h;
	int				expose;
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side_hit;
	int				height;
	int				width;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	t_keys			*key_pressed;
	t_ray			*ray;
	t_map			*map;
}					t_env;

typedef struct		s_thread
{
	t_env			*env;
	int				count;
	int				index;
	int				x;
	int				y;
}					t_thread;

void				get_map_width(t_env *env, int fd);
void				get_map_height(t_env *env, int fd);
void				store_map(t_env *env, int fd);
void				make_environment(void *mlx, t_env *env);
void				redraw(t_env *env);
void				set_hooks(t_env *env);
int					loop_hook(t_env *env);
int					exit_hook(t_env *env);
int					pressed_hook(int keycode, t_env *env);
int					released_hook(int keycode, t_env *env);
void				toggle_keys(int keycode, t_env *env, int toggle);
void				move_forward(t_env *env);
void				move_backward(t_env *env);
void				rotate_right(t_env *env);
void				rotate_left(t_env *env);
void				game_loop(t_env *env);
void				create_image(t_env *env);
int					put_line_to_img(t_env *env, int x, int y1, int y2);
unsigned int		get_wall_color(t_env *env);
unsigned int		wall_color_toggled(t_env *env);
int					floor_toggle(t_env *env);
int					wall_toggle(t_env *env);
int					space_hook(t_env *env);
void				close_doors(t_env *env);

#endif
