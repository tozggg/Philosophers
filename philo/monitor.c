/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:02:17 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:13:00 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		if (get_time() - philo[i].recent_eat > info->die_time)
		{
			info->end = 1;
			printf("%lldms\t%d died\n", \
				(get_time() - info->start_time), philo[i].index);
			return (true);
		}
		++i;
	}
	return (false);
}

static int	is_all_ate(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total)
	{
		if (philo[i].eat_count < info->must_eat)
			return (false);
		++i;
	}
	info->end = 1;
	printf("!! all ate check!!\n");
	return (true);
}

int	monitor(t_philo *philo, t_info *info)
{
	if (is_dead(philo, info))
		return (0);
	if (info->must_eat == -1)
		return (1);
	else if (is_all_ate(philo, info))
		return (0);
	else
		return (1);
}
