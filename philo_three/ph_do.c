/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_do.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:30:13 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:30:46 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	change_status(t_model *model, int status, sem_t *sem)
{
	long long	time;

	if (status == STATUS_WAIT)
	{
		model->philosopher->status = status;
		sem_post(sem);
		return (0);
	}
	time = time_now();
	if (status == STATUS_EAT)
	{
		print_status(STATUS_FORK, model->philosopher->num,
			time - model->time_start, model->sem_print);
		print_status(STATUS_FORK, model->philosopher->num,
			time - model->time_start, model->sem_print);
	}
	print_status(status, model->philosopher->num,
		time - model->time_start, model->sem_print);
	model->philosopher->status = status;
	return (0);
}

long long	ph_eat(t_model *model)
{
	long long	time;

	sem_wait(model->queue[model->philosopher->num - 1]);
	sem_wait(model->forks);
	sem_wait(model->forks);
	time = time_now();
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->sem_print);
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->sem_print);
	print_status(STATUS_EAT, model->philosopher->num,
		time - model->time_start, model->sem_print);
	model->philosopher->status = STATUS_EAT;
	sem_post(model->sem_forks_get);
	usleep(model->time_to_eat * 1000);
	model->c += 2;
	time = time_now();
	model->philosopher->time_last_eat = time;
	model->philosopher->times_eat++;
	sem_post(model->forks);
	sem_post(model->forks);
	sem_post((model->queue[model->philosopher->num % model->ph_count]));
	return (0);
}

long long	ph_sleep(t_model *model)
{
	change_status(model, STATUS_SLEEP, model->sem_status);
	usleep(model->time_to_sleep * 1000);
	return (0);
}

long long	ph_think(t_model *model)
{
	change_status(model, STATUS_THINK, model->sem_status);
	return (0);
}

int	ph_do(t_model *model)
{
	long long	time;

	if (model->philosopher->status == STATUS_CREATE)
		time = ph_eat(model);
	else if (model->philosopher->status == STATUS_SLEEP)
		time = ph_think(model);
	else if (model->philosopher->status == STATUS_EAT)
	{
		if (model->must_eat >= 0 && \
			model->philosopher->times_eat >= model->must_eat)
		{
			change_status(model, STATUS_SLEEP, model->sem_status);
			exit (2);
		}
		time = ph_sleep(model);
	}
	else if (model->philosopher->status == STATUS_THINK)
		time = ph_eat(model);
	return (0);
}
