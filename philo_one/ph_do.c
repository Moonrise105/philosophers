/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_do.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:48:01 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:48:15 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	change_status(t_model *model, int status, pthread_mutex_t *mutex)
{
	long long	time;

	pthread_mutex_lock(mutex);
	if (status == STATUS_WAIT)
	{
		model->philosopher->status = status;
		pthread_mutex_unlock(mutex);
		return (0);
	}
	time = time_now();
	if (status == STATUS_EAT)
	{
		print_status(STATUS_FORK, model->philosopher->num,
			time - model->time_start, model->mutex_print);
		print_status(STATUS_FORK, model->philosopher->num,
			time - model->time_start, model->mutex_print);
	}
	print_status(status, model->philosopher->num,
		time - model->time_start, model->mutex_print);
	model->philosopher->status = status;
	pthread_mutex_unlock(mutex);
	return (0);
}

long long	ph_eat(t_model *model)
{
	long long	time;

	change_status(model, STATUS_WAIT, model->mutex_forks_get);
	wait_queue(model);
	pthread_mutex_lock(model->philosopher->left_fork);
	pthread_mutex_lock(model->philosopher->right_fork);
	time = time_now();
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->mutex_print);
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->mutex_print);
	print_status(STATUS_EAT, model->philosopher->num,
		time - model->time_start, model->mutex_print);
	model->philosopher->status = STATUS_EAT;
	pthread_mutex_unlock(model->mutex_forks_get);
	pthread_mutex_unlock(model->philosopher->left_fork);
	pthread_mutex_unlock(model->philosopher->right_fork);
	usleep(model->time_to_eat * 1000);
	pthread_mutex_lock(model->philosopher->mutex_die);
	time = time_now();
	model->philosopher->time_last_eat = time;
	model->philosopher->times_eat++;
	pthread_mutex_unlock(model->philosopher->mutex_die);
	return (0);
}

long long	ph_sleep(t_model *model)
{
	change_status(model, STATUS_SLEEP, model->mutex_forks_get);
	usleep(model->time_to_sleep * 1000);
	return (0);
}

long long	ph_think(t_model *model)
{
	change_status(model, STATUS_THINK, model->mutex_forks_get);
	return (0);
}

long long	ph_do(t_model *model)
{
	long long	time;

	if (model->philosopher->status == STATUS_CREATE)
		time = ph_eat(model);
	else if (model->philosopher->status == STATUS_SLEEP)
		time = ph_think(model);
	else if (model->philosopher->status == STATUS_EAT)
	{
		if (check_eat_end(model))
		{
			pthread_mutex_lock(model->mutex_print);
			exit(0);
		}
		time = ph_sleep(model);
	}
	else if (model->philosopher->status == STATUS_THINK)
		time = ph_eat(model);
	return (time);
}
