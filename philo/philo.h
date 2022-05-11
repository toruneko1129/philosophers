/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:29 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/12 00:11:03 by hkawakit         ###   ########.fr       */
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
	suseconds_t			last_meal;
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

//utils.c
int		ft_atoi(const char *str);
t_bool	print_error(const char *s);

#endif
