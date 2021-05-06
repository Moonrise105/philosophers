/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:48:50 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:49:22 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	mutex_lst_init(pthread_mutex_t *mutex_lst, int num)
{
	int		i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&(mutex_lst[i]), NULL);
		++i;
	}
	return (0);
}

int	philosopher_lst_init(t_philosopher *ph_lst,
				int ph_count, pthread_mutex_t *forks,
				pthread_mutex_t *mutex_die)
{
	int		i;
	t_forks	lr_forks;

	i = 0;
	while (i < ph_count)
	{
		lr_forks.left_fork = &forks[i];
		lr_forks.right_fork = &forks[(i + 1) % ph_count];
		philosopher_init(i + 1, &lr_forks, &ph_lst[i], &mutex_die[i]);
		++i;
	}
	return (0);
}

int	check_status(t_philosopher *ph_lst, int ph_count)
{
	int		j;

	j = 0;
	while (j < ph_count)
	{
		if (!ph_lst[j].status)
			return (0);
		++j;
	}
	return (1);
}

int	print_status(int status, int num,
				long long time, pthread_mutex_t *mutex)
{
	char	*state;

	if (status == STATUS_DIE)
		state = "died";
	else if (status == STATUS_EAT)
		state = "is eating";
	else if (status == STATUS_SLEEP)
		state = "is sleeping";
	else if (status == STATUS_THINK)
		state = "is thinking";
	else if (status == STATUS_FORK)
		state = "has taken a fork";
	else
		return (-1);
	pthread_mutex_lock(mutex);
	printf("%lld %d %s\n", time, num, state);
	if (status != STATUS_DIE)
		pthread_mutex_unlock(mutex);
	return (0);
}

int	inc_no_eat(t_philosopher *ph_lst, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		ph_lst[i].times_not_eat++;
		++i;
	}
	return (0);
}
