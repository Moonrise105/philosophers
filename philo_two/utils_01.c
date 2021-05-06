/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:05:06 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:05:12 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int	change_queue(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->ph_count)
	{
		if (model->philosophers[i].queue > model->philosopher->queue)
			model->philosophers[i].queue--;
		++i;
	}
	model->philosopher->queue = model->ph_count;
	return (0);
}

int	check_queue(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->ph_count)
	{
		if (model->philosophers[i].queue < model->philosopher->queue && \
			model->philosophers[i].status == STATUS_WAIT)
			return (0);
		++i;
	}
	return (1);
}

int	get_access(t_model *model)
{
	int		ind_left;
	int		ind_right;
	int		ind_ph;
	int		code;

	ind_ph = model->philosopher->num - 1;
	ind_left = ind_ph - 1;
	if (ind_left < 0)
		ind_left = model->ph_count - 1;
	ind_right = (ind_ph + 1) % model->ph_count;
	sem_wait(model->sem_status);
	if (model->c <= 1)
	{
		sem_post(model->sem_status);
		return (0);
	}
	if (!check_queue(model))
	{
		sem_post(model->sem_status);
		return (0);
	}
	model->c -= 2;
	change_queue(model);
	sem_post(model->sem_status);
	return (1);
}
