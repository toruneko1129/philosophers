/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:29 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/23 10:56:30 by hkawakit         ###   ########.fr       */
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

# define STDERR 2

//settings
# define MAX_PHILO 200
# define MIN_TIME 60

//error message
# define EARG "[usage]: ./philo <philo> <die> <eat> <sleep> [must_eat]\n"
# define EVAL "Error: Invalid value\nphilo:~200 time:60~\n"
# define ESEM "Error: sem_open() failed\n"
# define EMALLOC "Error: malloc() failed\n"

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
	sem_t				*counting;
}	t_phbuffer;

//setup_rules_bonus.c
t_bool			get_args(const int argc, char **const argv,
					t_phbuffer *const phbuffer);
t_bool			init_semaphore(t_phbuffer *const phbuffer);

//utils_bonus.c
int				ft_atoi(const char *str);
t_bool			print_error(const char *s);

#endif
