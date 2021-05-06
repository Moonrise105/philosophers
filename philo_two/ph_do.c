/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_do.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:04:21 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:04:29 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	change_status(t_model *model, int status, sem_t *sem)
{
	long long	time;

	sem_wait(sem);
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
	sem_post(sem);
	return (0);
}

void	ph_eat(t_model *model)
{
	long long	time;

	change_status(model, STATUS_WAIT, model->sem_status);
	wait_queue(model);
	sem_wait(model->forks);
	sem_wait(model->forks);
	sem_wait(model->philosopher->sem_die);
	time = time_now();
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->sem_print);
	print_status(STATUS_FORK, model->philosopher->num,
		time - model->time_start, model->sem_print);
	print_status(STATUS_EAT, model->philosopher->num,
		time - model->time_start, model->sem_print);
	model->philosopher->status = STATUS_EAT;
	sem_post(model->sem_forks_get);
	sem_post(model->philosopher->sem_die);
	usleep(model->time_to_eat * 1000);
	sem_wait(model->sem_status);
	model->c += 2;
	model->philosopher->time_last_eat = time_now();
	model->philosopher->times_eat++;
	sem_post(model->sem_status);
	sem_post(model->forks);
	sem_post(model->forks);
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
		ph_eat(model);
	else if (model->philosopher->status == STATUS_SLEEP)
		time = ph_think(model);
	else if (model->philosopher->status == STATUS_EAT)
	{
		if (check_eat_end(model))
		{
			sem_wait(model->sem_print);
			return (-1);
		}
		time = ph_sleep(model);
	}
	else if (model->philosopher->status == STATUS_THINK)
		ph_eat(model);
	return (0);
}
