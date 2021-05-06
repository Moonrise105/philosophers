/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:28:45 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 14:29:07 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	queue_init(t_model *model)
{
	int	i;

	i = 0;
	while (i < model->ph_count)
	{
		if (i % 2)
			model->queue[i] = semaphore_open(ft_strjoin("sem_queue",
						ft_itoa(i + 1)), 1);
		else
			model->queue[i] = semaphore_open(ft_strjoin("sem_queue",
						ft_itoa(i + 1)), 0);
		++i;
	}
	return (0);
}

int	model_init(t_model *model)
{
	sem_t	*forks;
	sem_t	*sem_die_lst;
	int		run;

	run = 1;
	model->philosophers = malloc(sizeof(t_philosopher) * model->ph_count);
	forks = semaphore_open("forks", model->ph_count);
	sem_die_lst = malloc(sizeof(sem_t) * model->ph_count);
	model->sem_forks_get = semaphore_open("forks_get", 1);
	model->sem_print = semaphore_open("print", 1);
	model->sem_status = semaphore_open("status", 1);
	model->c = model->ph_count;
	sem_lst_init(sem_die_lst, model->ph_count);
	philosopher_lst_init(model->philosophers, model->ph_count,
		forks, sem_die_lst);
	model->queue = malloc(sizeof(sem_t *) * model->ph_count);
	queue_init(model);
	model->forks = forks;
	model->run = &run;
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

void	wait_ph(int count)
{
	int		status;

	while (count > 0)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 2)
				--count;
			else if (WEXITSTATUS(status) == 0)
				count = 0;
		}	
	}
}

int	main(int ac, char **av)
{
	t_model	*model;
	int		code;
	int		count;

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
	wait_ph(model->ph_count);
	return (0);
}
