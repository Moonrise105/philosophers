/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:04:42 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:04:54 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	wait_queue(t_model *model)
{
	int		can_get;

	can_get = 0;
	while (1)
	{
		sem_wait(model->sem_forks_get);
		can_get = get_access(model);
		if (can_get)
			return (1);
		sem_post(model->sem_forks_get);
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

int	check_eat_end(t_model *model)
{
	int		i;

	if (model->philosopher->times_eat < model->must_eat || \
		model->must_eat < 0)
		return (0);
	i = 0;
	while (i < model->ph_count)
	{
		if (model->philosophers[i].times_eat < model->must_eat)
			return (0);
		++i;
	}
	return (1);
}

int	str_digits(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	args_valid(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!str_digits(av[i]))
			return (0);
		++i;
	}
	return (1);
}
