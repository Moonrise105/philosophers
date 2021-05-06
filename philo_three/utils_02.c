/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:15:14 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:43:19 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long	tv_to_ms(struct timeval *tv)
{
	long long	time;

	time = tv->tv_sec * 1000LL + tv->tv_usec / 1000;
	return (time);
}

int	philosopher_init(int num, t_philosopher *ph, sem_t *sem_die)
{
	ph->num = num;
	ph->time_last_eat = 0LL;
	ph->status = 0;
	ph->times_not_eat = 0;
	ph->times_eat = 0;
	ph->sem_die = sem_die;
	return (0);
}

int	sem_lst_init(sem_t *sem_lst, int num)
{
	int		i;

	i = 0;
	while (i < num)
	{
		sem_lst[i] = *semaphore_open(ft_strjoin("die", ft_itoa(i + 1)), 1);
		++i;
	}
	return (0);
}

int	philosopher_lst_init(t_philosopher *ph_lst,
	int ph_count, sem_t *forks,
	sem_t *sem_die)
{
	int		i;

	i = 0;
	while (i < ph_count)
	{
		philosopher_init(i + 1, &ph_lst[i], &sem_die[i]);
		++i;
	}
	return (0);
}

sem_t	*semaphore_open(const char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0644, value));
}
