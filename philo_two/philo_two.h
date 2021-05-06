#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdlib.h>
# include <fcntl.h>
# define STATUS_CREATE 4
# define STATUS_THINK 5
# define STATUS_EAT 6
# define STATUS_SLEEP 7
# define STATUS_DIE 8
# define STATUS_FORK 9
# define STATUS_WAIT 10

typedef struct s_philosopher
{
	pthread_t	id;
	int			num;
	sem_t		*sem_die;
	long long	time_last_eat;
	int			status;
	int			times_not_eat;
	int			times_eat;
	int			queue;
}				t_philosopher;

typedef struct s_model
{
	t_philosopher	**queue;
	t_philosopher	*philosophers;
	t_philosopher	*philosopher;
	sem_t			*sem_print;
	sem_t			*sem_forks_get;
	sem_t			*forks;
	sem_t			*sem_status;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				ph_count;
	int				must_eat;
	int				c;
	int				*run;
	long long		time_start;
}				t_model;

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
sem_t		*semaphore_open(const char *name, int value);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
int			times_valid(t_model *model);
int			parse_args(int ac, char **av, t_model *model);
int			model_init(t_model *model);
int			init_args_check(int ac, char **av);
int			change_status(t_model *model, int status, sem_t *sem);
void		ph_eat(t_model *model);
long long	ph_sleep(t_model *model);
long long	ph_think(t_model *model);
int			ph_do(t_model *model);
void		*simulate_philosopher(void *model);
int			check_ph_die(t_model *model_new, int i);
void		*die_checker(void *model);
long long	set_time_start(t_model *model_lst, int size);
int			simulation_start(t_model *model);
int			wait_queue(t_model *model);
long long	time_now(void);
int			check_eat_end(t_model *model);
int			str_digits(const char *str);
int			args_valid(int ac, char **av);
int			inc_no_eat(t_model *model, int count);
int			check_no_eat(t_model *model);
int			change_queue(t_model *model);
int			check_queue(t_model *model);
int			get_access(t_model *model);
int			philosopher_init(int num, t_philosopher *ph, sem_t *sem_die);
int			sem_lst_init(sem_t *sem_lst, int num);
int			philosopher_lst_init(t_philosopher *ph_lst,
				int ph_count, sem_t *forks,
				sem_t *sem_die);
int			check_status(t_philosopher *ph_lst, int ph_count);
int			print_status(int status, int num,
				long long time, sem_t *sem);
long long	tv_to_ms(struct timeval *tv);
#endif