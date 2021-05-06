/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:29:35 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:29:46 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*die_checker(void *model)
{
	int			i;
	t_model		*model_new;
	long long	time;
	long long	time_last;

	model_new = (t_model *)model;
	while (1)
	{
		time = time_now();
		time_last = model_new->philosopher->time_last_eat;
		if (time - time_last > model_new->time_to_die)
		{
			print_status(STATUS_DIE, model_new->philosopher->num, \
					time - model_new->time_start, model_new->sem_print);
			exit(0);
		}
		usleep(100);
	}
	return (NULL);
}

void	*simulate_philosopher(void *model)
{
	t_model		model_new;
	long long	time;

	model_new = *((t_model *)model);
	model_new.philosopher->time_last_eat = model_new.time_start;
	model_new.philosopher->status = STATUS_CREATE;
	pthread_create(&model_new.philosopher->id, NULL, die_checker, model);
	while (ph_do(&model_new) >= 0)
	{
	}
	*((t_model *)model)->run = 0;
	return (NULL);
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
			time - model_new->time_start, model_new->sem_print);
		*model_new->run = 0;
	}
	return (0);
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

void	simulation_start(t_model *model)
{
	int				i;
	t_model			*models_lst;
	struct timeval	tmp;
	int				pid;

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
	while (i < model->ph_count)
	{
		pid = fork();
		if (pid == 0)
		{
			simulate_philosopher((void *)&models_lst[i]);
			break ;
		}
		++i;
	}
}
