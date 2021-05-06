/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 12:47:15 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:57:17 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	times_valid(t_model *model)
{
	if (model->ph_count > 100000 || model->ph_count <= 0)
		return (0);
	if (model->time_to_die < 0LL || model->time_to_eat < 0LL || \
		model->time_to_sleep < 0LL)
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

int	model_init(t_model *model)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_die_lst;

	model->philosophers = malloc(sizeof(t_philosopher) * model->ph_count);
	forks = malloc(sizeof(pthread_mutex_t) * model->ph_count);
	mutex_die_lst = malloc(sizeof(pthread_mutex_t) * model->ph_count);
	model->mutex_forks_get = malloc(sizeof(pthread_mutex_t));
	model->mutex_print = malloc(sizeof(pthread_mutex_t));
	model->run = 1;
	pthread_mutex_init(model->mutex_forks_get, NULL);
	pthread_mutex_init(model->mutex_print, NULL);
	mutex_lst_init(forks, model->ph_count);
	mutex_lst_init(mutex_die_lst, model->ph_count);
	philosopher_lst_init(model->philosophers, model->ph_count,
		forks, mutex_die_lst);
}

int	init_args_check(int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("Not enough arguments\n", 2);
		return (-1);
	}
	if (ac > 6)
	{
		ft_putstr_fd("Too many arguments\n", 2);
		return (-2);
	}
	if (!args_valid(ac, av))
	{
		ft_putstr_fd("Not valid arguments\n", 2);
		return (-3);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_model		*model;
	int			code;

	code = init_args_check(ac, av);
	if (code < 0)
		return (code);
	model = malloc(sizeof(t_model));
	parse_args(ac, av, model);
	if (!times_valid(model))
	{
		ft_putstr_fd("Not valid arguments\n", 2);
		return (-4);
	}
	model_init(model);
	simulation_start(model);
	while (model->run)
	{
	}
	return (0);
}
