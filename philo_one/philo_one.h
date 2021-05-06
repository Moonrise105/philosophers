/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moonrise <moonrise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:46:06 by moonrise          #+#    #+#             */
/*   Updated: 2021/04/19 12:57:47 by moonrise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# define STATUS_CREATE 4
# define STATUS_THINK 5
# define STATUS_EAT 6
# define STATUS_SLEEP 7
# define STATUS_DIE 8
# define STATUS_FORK 9
# define STATUS_WAIT 10

typedef struct s_philosopher
{
	pthread_t		id;
	int				num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex_die;
	long long		time_last_eat;
	int				status;
	int				times_not_eat;
	int				times_eat;
}				t_philosopher;

typedef struct s_model
{
	t_philosopher	*philosophers;
	t_philosopher	*philosopher;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_forks_get;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				ph_count;
	int				must_eat;
	int				run;
	long long		time_start;
}				t_model;

typedef struct s_forks
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_forks;

typedef struct s_message
{
	int			num;
	long long	time;
	int			status;
}				t_message;

int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int ch);
int			times_valid(t_model *model);
int			parse_args(int ac, char **av, t_model *model);
int			model_init(t_model *model);
int			init_args_check(int ac, char **av);
int			check_eat_end(t_model *model);
int			str_digits(const char *str);
int			args_valid(int ac, char **av);
int			change_status(t_model *model, int status, pthread_mutex_t *mutex);
long long	ph_eat(t_model *model);
long long	ph_sleep(t_model *model);
long long	ph_think(t_model *model);
long long	ph_do(t_model *model);
void		*simulate_philosopher(void *model);
int			check_ph_die(t_model *model_new, int i);
void		*die_checker(void *model);
long long	set_time_start(t_model *model_lst, int size);
int			simulation_start(t_model *model);
int			mutex_lst_init(pthread_mutex_t *mutex_lst, int num);
int			philosopher_lst_init(t_philosopher *ph_lst,
				int ph_count, pthread_mutex_t *forks,
				pthread_mutex_t *mutex_die);
int			check_status(t_philosopher *ph_lst, int ph_count);
int			print_status(int status, int num,
				long long time, pthread_mutex_t *mutex);
int			inc_no_eat(t_philosopher *ph_lst, int count);
long long	tv_to_ms(struct timeval *tv);
int			philosopher_init(int num, t_forks *forks,
				t_philosopher *ph, pthread_mutex_t *mutex_die);
int			get_access(t_model *model);
int			wait_queue(t_model *model);
long long	time_now(void);
#endif
