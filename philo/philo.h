/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taejkim <taejkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:00:13 by taejkim           #+#    #+#             */
/*   Updated: 2021/11/12 19:21:15 by taejkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

# define DONE 1
# define FAIL 0

typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_info
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
}	t_info;

typedef struct s_philo
{
	t_info		*info;
	t_thread	*th;
	t_mutex		*l;
	t_mutex		*r;
	long long	recent_eat;
	int			index;
	int			eat_count;
	int			has_fork;
}	t_philo;

int			usage_error(void);
void		argument_error(void);
int			ft_atoi(const char *nptr);
long long	get_time(void);
void		print_msg(t_philo *philo, char *msg);

int			init_info(t_info **ptr, int ac, char *av[]);
int			init_philo(t_philo **ptr, t_info *info);

int			monitor(t_philo *philo, t_info *info);

int			take_fork(t_philo *philo);
int			eating(t_philo *philo);
void		put_fork(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);

void		*routine(void *ptr);
int			create(t_philo *philo, t_info *info);

#endif
