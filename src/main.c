/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 19:13:35 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 17:01:26 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	main(int ac, char **av)
{
	void	*mlx;
	t_env	*env;
	int		fd;

	if (ac != 2)
		ft_error("Usage: ./wolf3d maps/<map name>");
	if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
		ft_error("Error: Failed to allocate memory line 23 main.c");
	if (!(env->map = (t_map*)ft_memalloc(sizeof(t_map))))
		ft_error("Error: Failed to allocate memory line 25 main.c");
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Error: Failed to open map. Check name and try again.");
	get_map_width(env, fd);
	get_map_height(env, fd);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_error("Error: Reopening of map failed.");
	store_map(env, fd);
	mlx = mlx_init();
	make_environment(mlx, env);
	create_image(env);
	env->win = mlx_new_window(mlx, env->width, env->height, "Wolf 3D");
	set_hooks(env);
	mlx_loop_hook(mlx, loop_hook, env);
	mlx_loop(mlx);
}
