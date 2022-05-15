/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:29 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/15 15:58:02 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define STDERR 2

//error message
# define EARG "[usage]: ./philo <philo> <die> <eat> <sleep> [must_eat]\n"
# define EVAL "Error: Invalid value\n"
# define EMALLOC "Error: malloc() failed\n"
# define EMUTEX "Error: pthread_mutex_init() failed\n"

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
	int					left_fork;
	int					right_fork;
	int					cnt_ate;
	long				last_meal;
	pthread_t			thread;
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
	t_bool				end;
	pthread_mutex_t		*fork;
	pthread_mutex_t		eating;
	pthread_mutex_t		writing;
	struct s_philo		*philo;
}	t_phbuffer;

//setup_rules.c
t_bool	get_args(int argc, char **argv, t_phbuffer *phbuffer);
t_bool	init_mutex(t_phbuffer *phbuffer);
t_bool	init_philo(t_phbuffer *phbuffer);

//philo_routine.c
void	*philo_routine(void *arg);

//utils.c
int		ft_atoi(const char *str);
t_bool	print_error(const char *s);

//utils2.c
long	get_timestamp(void);
void	print_action(t_phbuffer *phbuffer, int id, const char *action);

#endif
