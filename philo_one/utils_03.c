/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:15:14 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:50:09 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
