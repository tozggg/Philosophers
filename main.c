/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:38:36 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/09 19:29:30 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef pthread_t		t_thread;
typedef pthread_mutex_t t_mutex;

typedef struct	s_info
{
	t_mutex		**fork;
	t_mutex		*print;
	long long	start_time;
	int			total;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			must_eat;
}				t_info;

typedef struct	s_philo
{
	t_info		*info;
	t_thread	*th;
	t_mutex		*l;
	t_mutex		*r;
	long long	recent_eat;
	int			index;
	int			eat_count;
}				t_philo;

int	usage_error(void)
{
	printf("%s\n", "Error\n");
	printf("%s\n", "usage: ./philo [philo_num] [time_to_die] \
			[time_to_eat] [time_to_sleep] ([must_eat])");
	return (EXIT_FAILURE);
}

void argument_error(void)
{
	printf("%s\n", "Error\n");
	printf("%s\n", "usage: argument is positive integer");
}

int		ft_atoi(const char *nptr)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (nptr[i])
	{
		if (!('0' <= nptr[i] && nptr[i] <= '9'))
			return (0);
		else
			res = (nptr[i] - '0') + (res * 10);
		++i;
	}
	return (res);
}

int	test_argument(t_info *info)
{
	if (!info->total || !info->die_time || \
		!info->eat_time || !info->sleep_time || !info->must_eat)
	{
		argument_error();
		return (0);
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

int	make_fork(t_info *info)
{
	t_mutex **fork_set;
	t_mutex *fork;
	int 	i;

	fork_set = (t_mutex **)malloc(sizeof(t_mutex *) * info->total);
	if (!fork_set)
		return (0);
	i = 0;
	while (i < info->total)
	{
		fork = (t_mutex *)malloc(sizeof(t_mutex));
		if (!fork)
			return (0);
		if (pthread_mutex_init(fork, NULL))
			return (0);
		fork_set[i] = fork;
		++i;
	}
	info->fork = fork_set;	
}

int	make_print(t_info *info)
{
	t_mutex *print;

	print = (t_mutex *)malloc(sizeof(t_mutex));
	if (!print)
		return (0);
	if (pthread_mutex_init(print, NULL))
		return (0);
	info->print = print;
}

int	init_info(t_info *info, int ac, char *av[])
{
	info->total = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = -1;
	if (!test_argument(info))
		return (0);
	if (!make_fork(info) || !make_print(info))
		return (0);
	info->start_time = get_time();
	return (1);
}
/*
int	init_philo(t_philo **ptr, t_info *info)
{
	t_philo *philo_set;
	int		i;

	philo_set = (t_philo *)malloc(sizeof(t_philo) * info->total);
	if (!philo_set)
		return (0);
	i = 0;
	while (i < info->total)
	{
		philo_set[i].info = info;
		philo_set[i].th = (t_thread *)malloc(sizeof(t_thread));
		if (!philo_set[i].th)
			return (0);
		philo_set[i].l = info->fork[i];
		philo_set[i].r = info->fork[i + 1 % info->total];
		//이거 가능?
		philo_set[i].recent_eat = get_time();
		philo_set[i].index = i + 1;
		philo_set[i].eat_count = 0;
		++i;
	}
	ptr = &philo_set;
	return (1);
}
*/
int	main(int ac, char *av[])
{
	t_info	info;
	t_philo	*philo;

	if (!(ac == 5 || ac == 6))
		return (usage_error());
	if (!init_info(&info, ac, av))
		return (EXIT_FAILURE);
	if (!init_philo(&philo, &info))
		return (EXIT_FAILURE);
	
	while(1)
	{
		
	}

	return (EXIT_SUCCESS);
}
