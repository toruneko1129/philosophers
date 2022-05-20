/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/20 15:15:41 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		monitor_death(phbuffer, philo);
		monitor_full(phbuffer, philo);
		usleep(100);
	}
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
	pthread_mutex_destroy(&(phbuffer->checker));
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

	memset(&phbuffer, 0, sizeof(phbuffer));
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	if (phbuffer.num_of_philo == 1)
		return (philo_solo(&phbuffer));
	start_routine(&phbuffer);
	destroy_phbuffer(&phbuffer);
	return (EXIT_SUCCESS);
}
