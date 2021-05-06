/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:31:31 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:28 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

int	times_valid(t_model *model)
{
	if (model->ph_count > 100000 || model->ph_count <= 0)
		return (0);
	if (model->time_to_die < 0LL || model->time_to_eat < 0LL || \
		model->time_to_sleep < 0LL || model->must_eat == 0)
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_model *model)
{
	model->ph_count = ft_atoi(av[1]);
	model->time_to_die = ft_atoi(av[2]);
	model->time_to_eat = ft_atoi(av[3]);
	model->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		model->must_eat = ft_atoi(av[5]);
	else
		model->must_eat = -1;
	return (0);
}
