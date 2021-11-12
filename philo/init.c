/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:02:49 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:13:41 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	test_argument(t_info *info)
{
	if (!info->total || !info->die_time || \
		!info->eat_time || !info->sleep_time || !info->must_eat)
	{
		argument_error();
		return (FAIL);
	}
	return (DONE);
}

static int	make_fork(t_info *info)
{
	t_mutex	**fork_set;
	t_mutex	*fork;
	int		i;

	fork_set = (t_mutex **)malloc(sizeof(t_mutex *) * info->total);
	if (!fork_set)
		return (FAIL);
	i = 0;
	while (i < info->total)
	{
		fork = (t_mutex *)malloc(sizeof(t_mutex));
		if (!fork)
			return (FAIL);
		if (pthread_mutex_init(fork, NULL))
			return (FAIL);
		fork_set[i] = fork;
		++i;
	}
	info->fork = fork_set;
	return (DONE);
}

static int	make_print(t_info *info)
{
	t_mutex	*print;

	print = (t_mutex *)malloc(sizeof(t_mutex));
	if (!print)
		return (FAIL);
	if (pthread_mutex_init(print, NULL))
		return (FAIL);
	info->print = print;
	return (DONE);
}

int	init_info(t_info **ptr, int ac, char *av[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (FAIL);
	info->total = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = -1;
	if (!test_argument(info))
		return (FAIL);
	if (!make_fork(info) || !make_print(info))
		return (FAIL);
	info->start_time = get_time();
	info->end = 0;
	*ptr = info;
	return (DONE);
}

int	init_philo(t_philo **ptr, t_info *info)
{
	t_philo	*philo_set;
	int		i;

	philo_set = (t_philo *)malloc(sizeof(t_philo) * info->total);
	if (!philo_set)
		return (FAIL);
	i = 0;
	while (i < info->total)
	{
		philo_set[i].info = info;
		philo_set[i].th = (t_thread *)malloc(sizeof(t_thread));
		if (!philo_set[i].th)
			return (FAIL);
		philo_set[i].l = info->fork[i];
		philo_set[i].r = info->fork[(i + 1) % info->total];
		philo_set[i].recent_eat = get_time();
		philo_set[i].index = i + 1;
		philo_set[i].eat_count = 0;
		philo_set[i].has_fork = 0;
		++i;
	}
	*ptr = philo_set;
	return (DONE);
}
