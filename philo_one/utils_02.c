/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:49:52 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:57:52 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long long	tv_to_ms(struct timeval *tv)
{
	long long	time;

	time = tv->tv_sec * 1000LL + tv->tv_usec / 1000;
	return (time);
}

int	philosopher_init(int num, t_forks *forks,
			t_philosopher *ph, pthread_mutex_t *mutex_die)
{
	ph->left_fork = forks->left_fork;
	ph->right_fork = forks->right_fork;
	ph->num = num;
	ph->time_last_eat = 0LL;
	ph->status = 0;
	ph->times_not_eat = 0;
	ph->times_eat = 0;
	ph->mutex_die = mutex_die;
	return (0);
}

int	get_access(t_model *model)
{
	int		ind_left;
	int		ind_right;
	int		ind_ph;

	ind_ph = model->philosopher->num - 1;
	ind_left = ind_ph - 1;
	if (ind_left < 0)
		ind_left = model->ph_count - 1;
	ind_right = (ind_ph + 1) % model->ph_count;
	pthread_mutex_lock(model->mutex_forks_get);
	if (model->philosophers[ind_left].status != STATUS_EAT && \
		model->philosophers[ind_right].status != STATUS_EAT)
	{
		if (model->philosophers[ind_left].times_not_eat >= 2 || \
			model->philosophers[ind_right].times_not_eat >= 2 || \
			(!(model->philosopher->num % 2) && \
			(!model->philosophers[ind_left].times_eat || \
			!model->philosophers[ind_right].times_eat)))
			return (0);
		model->philosophers[ind_left].times_not_eat++;
		model->philosophers[ind_right].times_not_eat++;
		model->philosopher->times_not_eat = 0;
		return (1);
	}
	return (0);
}

int	wait_queue(t_model *model)
{
	int		can_get;

	can_get = 0;
	while (1)
	{
		can_get = get_access(model);
		if (can_get)
			return (1);
		pthread_mutex_unlock(model->mutex_forks_get);
		usleep(100);
	}
	return (0);
}

long long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (tv_to_ms(&time));
}
