/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_rules_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:18:37 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/23 10:57:37 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_bool	get_args(const int argc, char **const argv,
	t_phbuffer *const phbuffer)
{
	if (argc != 5 && argc != 6)
		return (print_error(EARG));
	phbuffer->num_of_philo = ft_atoi(argv[1]);
	phbuffer->time_to_die = ft_atoi(argv[2]);
	phbuffer->time_to_eat = ft_atoi(argv[3]);
	phbuffer->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		phbuffer->num_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		phbuffer->opt = TRUE;
	}
	if (phbuffer->num_of_philo <= 0 || phbuffer->num_of_philo > MAX_PHILO
		|| phbuffer->time_to_die < MIN_TIME || phbuffer->time_to_eat < MIN_TIME
		|| phbuffer->time_to_sleep < MIN_TIME)
		return (print_error(EVAL));
	if (phbuffer->opt && phbuffer->num_of_times_each_philo_must_eat <= 0)
		return (print_error(EVAL));
	return (FALSE);
}

t_bool	init_semaphore(t_phbuffer *const phbuffer)
{
	sem_unlink("/philo_fork");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_counting");
	phbuffer->fork = sem_open("/philo_fork", O_CREAT,
			S_IREAD | S_IWRITE, phbuffer->num_of_philo);
	phbuffer->eating = sem_open("/philo_eating", O_CREAT,
			S_IREAD | S_IWRITE, 1);
	phbuffer->writing = sem_open("/philo_writing", O_CREAT,
			S_IREAD | S_IWRITE, 1);
	phbuffer->counting = sem_open("/philo_counting", O_CREAT,
			S_IREAD | S_IWRITE, 1);
	if (phbuffer->fork == SEM_FAILED || phbuffer->eating == SEM_FAILED
		|| phbuffer->writing == SEM_FAILED || phbuffer->counting == SEM_FAILED)
		return (print_error(ESEM));
	return (FALSE);
}
