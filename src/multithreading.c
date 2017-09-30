/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etregoni <etregoni@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 19:23:09 by etregoni          #+#    #+#             */
/*   Updated: 2017/09/27 17:13:12 by etregoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

pthread_t	create_thread(t_env *env, int thread_index, int thread_count)
{
	pthread_t	pthread;
	t_thread	*thread;
	thread = (t_thread*)malloc(sizeof(t_thread));
	thread->count = thread_count;
	thread->index = thread_index;
	thread->env = env;
	pthread_create(&pthread, NULL, (void*)game_loop, thread);
	return (pthread);
}

void	init_thread(t_env *env)
{
	int			i;
	int			num;
	pthread_t	threads[NUM_THREADS];

	num = NUM_THREADS;
	i = 1;
	while (i < num + 1)
	{
		threads[i - 1] = create_thread(env, i, num);
		i++;
	}
	i = 0;
	while (i < num)
		pthread_join(threads[i++], NULL);
}
