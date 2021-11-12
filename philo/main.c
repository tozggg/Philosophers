/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:38:36 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:14:46 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (!take_fork(philo))
			break ;
		if (!eating(philo))
			break ;
		put_fork(philo);
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	if (philo->has_fork)
		put_fork(philo);
	return (NULL);
}

int	create(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		if (pthread_create(philo[i].th, NULL, routine, (t_philo *)&philo[i]) \
			|| pthread_detach(*(philo[i].th)))
			return (FAIL);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < info->total)
	{
		if (pthread_create(philo[i].th, NULL, routine, (t_philo *)&philo[i]) \
			|| pthread_detach(*(philo[i].th)))
			return (FAIL);
		i += 2;
	}
	return (DONE);
}

int	main(int ac, char *av[])
{
	t_philo	*philo;
	t_info	*info;

	if (!(ac == 5 || ac == 6))
		return (usage_error());
	if (!init_info(&info, ac, av))
		return (EXIT_FAILURE);
	if (!init_philo(&philo, info))
		return (EXIT_FAILURE);
	if (!create(philo, info))
		return (EXIT_FAILURE);
	while (monitor(philo, info))
	{
	}
	return (EXIT_SUCCESS);
}
