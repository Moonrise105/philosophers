/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:32:05 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:37:00 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int	inc_no_eat(t_model *model, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (model->philosophers[i].status == STATUS_WAIT || \
			model->philosophers[i].status == STATUS_CREATE)
			model->philosophers[i].times_not_eat++;
		++i;
	}
	return (0);
}

int	check_no_eat(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->ph_count)
	{
		if ((i + 1) != model->philosopher->num)
		{
			if (model->philosophers[i].times_not_eat >= (model->ph_count - 1))
				return (0);
		}
		++i;
	}
	return (1);
}

long long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (tv_to_ms(&time));
}
