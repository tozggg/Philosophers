/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:03:50 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:16:09 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->info->end)
		return (0);
	pthread_mutex_lock(philo->l);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->r);
	print_msg(philo, "has taken a fork");
	philo->has_fork = 1;
	return (1);
}

int	eating(t_philo *philo)
{
	long long	eat_start;

	if (philo->info->end)
		return (0);
	print_msg(philo, "is eating");
	++(philo->eat_count);
	philo->recent_eat = get_time();
	eat_start = get_time();
	while (get_time() - eat_start < philo->info->eat_time)
		usleep(100);
	return (1);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	philo->has_fork = 0;
}

int	sleeping(t_philo *philo)
{
	long long	sleep_start;

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
