/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:18:37 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/16 11:03:59 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		|| phbuffer->time_to_die <= 0 || phbuffer->time_to_eat <= 0
		|| phbuffer->time_to_sleep <= 0)
		return (print_error(EVAL));
	if (phbuffer->opt && phbuffer->num_of_times_each_philo_must_eat <= 0)
		return (print_error(EVAL));
	return (FALSE);
}

t_bool	init_mutex(t_phbuffer *const phbuffer)
{
	int		i;

	if (pthread_mutex_init(&(phbuffer->eating), NULL)
		|| pthread_mutex_init(&(phbuffer->writing), NULL)
		|| pthread_mutex_init(&(phbuffer->counting), NULL)
		|| pthread_mutex_init(&(phbuffer->checker), NULL))
		return (print_error(EMUTEX));
	phbuffer->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* phbuffer->num_of_philo);
	if (phbuffer->fork == NULL)
		return (print_error(EMALLOC));
	i = -1;
	while (++i < phbuffer->num_of_philo)
	{
		if (pthread_mutex_init(&(phbuffer->fork[i]), NULL))
		{
			free(phbuffer->fork);
			phbuffer->fork = NULL;
			return (print_error(EMUTEX));
		}
	}
	return (FALSE);
}

t_bool	init_philo(t_phbuffer *const phbuffer)
{
	int		i;
	t_philo	*philo;

	phbuffer->philo = (t_philo *)malloc(sizeof(t_philo)
			* phbuffer->num_of_philo);
	if (phbuffer->philo == NULL)
	{
		free(phbuffer->fork);
		phbuffer->fork = NULL;
		return (print_error(EMALLOC));
	}
	i = -1;
	while (++i < phbuffer->num_of_philo)
	{
		philo = &(phbuffer->philo[i]);
		philo->id = i + 1;
		philo->left_fork = i;
		philo->right_fork = (i + 1) % phbuffer->num_of_philo;
		philo->cnt_ate = 0;
		philo->last_meal = 0;
		philo->phbuffer = phbuffer;
	}
	return (FALSE);
}
