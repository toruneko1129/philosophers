/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/12 00:19:48 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	phbuffer_init(t_phbuffer *phbuffer)
{
	phbuffer->num_of_philo = 0;
	phbuffer->time_to_die = 0;
	phbuffer->time_to_eat = 0;
	phbuffer->time_to_sleep = 0;
	phbuffer->num_of_times_each_philo_must_eat = 0;
	phbuffer->opt = FALSE;
	phbuffer->end = FALSE;
	phbuffer->fork = NULL;
	phbuffer->philo = NULL;
}

static t_bool	setup_rules(int argc, char **argv, t_phbuffer *phbuffer)
{
	if (get_args(argc, argv, phbuffer) || init_mutex(phbuffer)
		|| init_philo(phbuffer))
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;
	int			i;

	phbuffer_init(&phbuffer);
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	pthread_mutex_destroy(&(phbuffer.eating));
	pthread_mutex_destroy(&(phbuffer.writing));
	i = -1;
	while (++i < phbuffer.num_of_philo)
		pthread_mutex_destroy(&(phbuffer.fork[i]));
	free(phbuffer.fork);
	free(phbuffer.philo);
	return (EXIT_SUCCESS);
}
