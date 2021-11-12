/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:01:33 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:11:11 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage_error(void)
{
	printf("%s\n", "Error");
	printf("%s\n", "usage: ./philo [philo_num] [time_to_die] "\
	 				"[time_to_eat] [time_to_sleep] ([must_eat])");
	return (EXIT_FAILURE);
}

void	argument_error(void)
{
	printf("%s\n", "Error");
	printf("%s\n", "usage: argument is positive integer");
}

int	ft_atoi(const char *nptr)
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

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
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
	printf("%s\n", msg);
	pthread_mutex_unlock(philo->info->print);
}
