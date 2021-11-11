/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:38:36 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/10 21:42:37 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>

#define DONE 1
#define FAIL 0

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
	int			end;
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
	printf("%s\n", "Error");
	printf("%s\n", "usage: ./philo [philo_num] [time_to_die] "\
	 				"[time_to_eat] [time_to_sleep] ([must_eat])");
	return (EXIT_FAILURE);
}

void argument_error(void)
{
	printf("%s\n", "Error");
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
			return (FAIL);
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
		return (FAIL);
	}
	return (DONE);
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

int	make_print(t_info *info)
{
	t_mutex *print;

	print = (t_mutex *)malloc(sizeof(t_mutex));
	if (!print)
		return (FAIL);
	if (pthread_mutex_init(print, NULL))
		return (FAIL);
	info->print = print;
	return (DONE);
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
		return (FAIL);
	if (!make_fork(info) || !make_print(info))
		return (FAIL);
	info->start_time = get_time();
	info->end = 0;
	return (DONE);
}

int	init_philo(t_philo **ptr, t_info *info)
{
	t_philo *philo_set;
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
		++i;
	}
	*ptr = philo_set;
	return (DONE);
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->info->print);
	if (philo->info->end)
	{
		pthread_mutex_unlock(philo->info->print);
		return ;
	}
	printf("%lld%s\t", (get_time() - philo->info->start_time), "ms");
	printf("%d ", philo->index);
	printf("%s", msg);
	printf("\t%d\n", philo->eat_count);
	pthread_mutex_unlock(philo->info->print);
}

int	take_fork(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	pthread_mutex_lock(philo->l);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->r);
	print_msg(philo, "has taken a fork");
	return (1);
}

int	eating(t_philo *philo)
{
	long long eat_start;
	
	if (philo->info->end)
		return (0);
	print_msg(philo, "is eating");
	eat_start = get_time();
	while (get_time() - eat_start < philo->info->eat_time)
		usleep(100);
	philo->recent_eat = get_time();
	++(philo->eat_count);
	return (1);
}

int	put_fork(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	return (1);
}

int	sleeping(t_philo *philo)
{
	long long sleep_start;

	if (philo->info->end)
		return (0);
	print_msg(philo, "is sleeping");
	sleep_start = get_time();
	while (get_time() - sleep_start < philo->info->sleep_time)
		usleep(100);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	print_msg(philo, "is thinking");
	return (1);
}

void	*routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (!take_fork(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!put_fork(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		if (!thinking(philo))
			return (NULL);
	}
}

int	create(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->total)
	{
		if (pthread_create(philo[i].th, NULL, routine, &philo[i])\
			 || pthread_detach(*(philo[i].th)))
			return (FAIL);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < info->total)
	{
		if (pthread_create(philo[i].th, NULL, routine, (t_philo *)&philo[i])\
			 || pthread_detach(*(philo[i].th)))
			return (FAIL);
		i += 2;
	}
	return (DONE);
}

int	is_dead(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->total)
	{
		if (get_time() - philo[i].recent_eat > info->die_time)
		{
			print_msg(philo, "is died");
			return (true);
		}
		++i;
	}
	return (false);
}

int	is_all_ate(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (i < info->total)
	{
		if (philo[i].eat_count < info->must_eat)
			return (false);
		++i;
	}
	printf("!! all ate !!\n");
	return (true);
}

int	monitor(t_philo *philo, t_info *info)
{
	if (is_dead(philo, info))
	{
		info->end = 1;
		return (0);
	}
	if (info->must_eat == -1)
		return (1);
	else if (is_all_ate(philo, info))
	{
		info->end = 1;
		return (0);
	}
	else
		return (1);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_info	info;

	if (!(ac == 5 || ac == 6))
		return (usage_error());
	if (!init_info(&info, ac, av))
		return (EXIT_FAILURE);
	if (!init_philo(&philo, &info))
		return (EXIT_FAILURE);
	if (!create(philo, &info))
		return (EXIT_FAILURE);	
	while (monitor(philo, &info))
	{
	}
	return (EXIT_SUCCESS);
}
