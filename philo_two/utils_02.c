/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:05:30 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:05:37 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	philosopher_init(int num, t_philosopher *ph, sem_t *sem_die)
{
	ph->num = num;
	ph->time_last_eat = 0LL;
	ph->status = 0;
	ph->times_not_eat = 0;
	ph->times_eat = 0;
	ph->sem_die = sem_die;
	ph->queue = num;
	return (0);
}

int	sem_lst_init(sem_t *sem_lst, int num)
{
	int		i;
	char	*nbr;
	char	*name;

	i = 0;
	while (i < num)
	{
		nbr = ft_itoa(i + 1);
		name = ft_strjoin("die", nbr);
		free(nbr);
		sem_lst[i] = *semaphore_open(name, 1);
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
	long long time, sem_t *sem)
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
	sem_wait(sem);
	printf("%lld %d %s\n", time, num, state);
	if (status != STATUS_DIE)
		sem_post(sem);
	return (0);
}
