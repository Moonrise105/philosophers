/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:47:12 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:57:02 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*simulate_philosopher(void *model)
{
	t_model		model_new;
	long long	time;

	model_new = *((t_model *)model);
	model_new.philosopher->time_last_eat = model_new.time_start;
	model_new.philosopher->status = STATUS_CREATE;
	while (1)
		ph_do(&model_new);
}

int	check_ph_die(t_model *model_new, int i)
{
	long long	time;
	long long	time_last;

	time = time_now();
	time_last = model_new->philosophers[i].time_last_eat;
	if (time - time_last > model_new->time_to_die)
	{
		print_status(STATUS_DIE, model_new->philosophers[i].num, \
					time - model_new->time_start, model_new->mutex_print);
		model_new->run = 0;
	}
	return (0);
}

void	*die_checker(void *model)
{
	int			i;
	t_model		*model_new;

	model_new = (t_model *)model;
	while (!check_status(model_new->philosophers, model_new->ph_count))
	{
	}
	while (1)
	{
		i = 0;
		while (i < model_new->ph_count)
		{
			pthread_mutex_lock(model_new->philosophers[i].mutex_die);
			check_ph_die(model_new, i);
			pthread_mutex_unlock(model_new->philosophers[i].mutex_die);
			++i;
		}
		usleep(100);
	}
	return (NULL);
}

long long	set_time_start(t_model *model_lst, int size)
{
	int				i;
	struct timeval	time;
	long long		time_ms;

	i = 0;
	gettimeofday(&time, NULL);
	time_ms = tv_to_ms(&time);
	while (i < size)
	{
		model_lst[i].time_start = time_ms;
		++i;
	}
	return (time_ms);
}

int	simulation_start(t_model *model)
{
	int				i;
	t_model			*models_lst;
	pthread_t		id;
	struct timeval	tmp;

	models_lst = malloc(sizeof(t_model) * model->ph_count);
	i = 0;
	while (i < model->ph_count)
	{
		model->philosopher = &model->philosophers[i];
		models_lst[i] = *model;
		++i;
	}
	i = 0;
	model->time_start = set_time_start(models_lst, model->ph_count);
	pthread_create(&id, NULL, die_checker, (void *)model);
	while (i < model->ph_count)
	{
		pthread_create(&models_lst[i].philosopher->id, NULL, \
						simulate_philosopher, (void *)&models_lst[i]);
		++i;
	}
	return (0);
}
