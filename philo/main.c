/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/16 17:46:18 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	phbuffer_init(t_phbuffer *const phbuffer)
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

static t_bool	setup_rules(const int argc, char **const argv,
	t_phbuffer *const phbuffer)
{
	if (get_args(argc, argv, phbuffer))
		return (TRUE);
	if (phbuffer->num_of_philo == 1)
		return (FALSE);
	if (init_mutex(phbuffer) || init_philo(phbuffer))
		return (TRUE);
	return (FALSE);
}

static void	start_routine(t_phbuffer *const phbuffer)
{
	t_philo *const	philo = phbuffer->philo;
	int				i;

	i = -1;
	while (++i < phbuffer->num_of_philo)
	{
		philo[i].last_meal = get_timestamp();
		pthread_create(&(philo[i].thread), NULL, philo_routine, &(philo[i]));
	}
	while (!(phbuffer->end))
		monitor_death(phbuffer, philo);
}

static void	destroy_phbuffer(t_phbuffer *const phbuffer)
{
	int		i;

	i = -1;
	while (++i < phbuffer->num_of_philo)
		pthread_join(phbuffer->philo[i].thread, NULL);
	pthread_mutex_destroy(&(phbuffer->eating));
	pthread_mutex_destroy(&(phbuffer->writing));
	pthread_mutex_destroy(&(phbuffer->counting));
	i = -1;
	while (++i < phbuffer->num_of_philo)
		pthread_mutex_destroy(&(phbuffer->fork[i]));
	free(phbuffer->fork);
	phbuffer->fork = NULL;
	free(phbuffer->philo);
	phbuffer->philo = NULL;
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	phbuffer_init(&phbuffer);
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	if (phbuffer.num_of_philo == 1)
		return (philo_solo(&phbuffer));
	start_routine(&phbuffer);
	destroy_phbuffer(&phbuffer);
	return (EXIT_SUCCESS);
}
