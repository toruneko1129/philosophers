/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:29 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/26 22:52:32 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

# define STDERR 2

//settings
# define MAX_PHILO 200
# define MIN_TIME 60

//error message
# define EARG "[usage]: ./philo <philo> <die> <eat> <sleep> [must_eat]\n"
# define EVAL "Error: Invalid value\nphilo:~200 time:60~\n"
# define ESEM "Error: sem_open() failed\n"
# define EMALLOC "Error: malloc() failed\n"
# define EFORK "Error: fork() failed\n"

//philo message
# define PFORK "has taken a fork"
# define PEAT "is eating"
# define PSLEEP "is sleeping"
# define PTHINK "is thinking"
# define PDIED "died"

typedef int	t_bool;

typedef enum e_boolean
{
	FALSE,
	TRUE
}	t_boolean;

typedef struct s_philo
{
	int					id;
	int					cnt_ate;
	unsigned long		last_meal;
	pthread_t			monitor;
	pid_t				pid;
	struct s_phbuffer	*phbuffer;
}	t_philo;

typedef struct s_phbuffer
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_times_each_philo_must_eat;
	t_bool				opt;
	sem_t				*fork;
	sem_t				*eating;
	sem_t				*writing;
	struct s_philo		*philo;
}	t_phbuffer;

//setup_rules_bonus.c
t_bool			get_args(const int argc, char **const argv,
					t_phbuffer *const phbuffer);
t_bool			init_semaphore(t_phbuffer *const phbuffer);
t_bool			init_philo(t_phbuffer *const phbuffer);

//philo_routine_bonus.c
int				philo_solo(t_phbuffer *const phbuffer);
void			philo_routine(t_philo *const philo);

//monitor_bonus.c
void			*monitor_philo(void *arg);

//utils_bonus.c
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
t_bool			print_error(const char *s);

//utils2_bonus.c
unsigned long	get_timestamp(void);
void			print_action(t_phbuffer *const phbuffer, const int id,
					const char *action);

#endif
