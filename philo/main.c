/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/15 22:01:39 by hkawakit         ###   ########.fr       */
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
	if (get_args(argc, argv, phbuffer) || init_mutex(phbuffer)
		|| init_philo(phbuffer))
		return (TRUE);
	return (FALSE);
}

static t_bool	start_routine(t_phbuffer *phbuffer)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = phbuffer->philo;
	while (++i < phbuffer->num_of_philo)
		pthread_create(&(philo[i].thread), NULL, philo_routine, &(philo[i]));
	while (!phbuffer->end)
	{
		i = -1;
		while (++i < phbuffer->num_of_philo)
		{
			pthread_mutex_lock(&phbuffer->eating);
			if (get_timestamp() - philo[i].last_meal > phbuffer->time_to_die)
			{
				print_action(phbuffer, philo[i].id, PDIED);
				phbuffer->end = 1;
			}
			pthread_mutex_unlock(&phbuffer->eating);
		}
		if (phbuffer->end)
			break ;
		i = 0;
		while (phbuffer->opt && i < phbuffer->num_of_philo
			&& philo[i].cnt_ate >= phbuffer->num_of_times_each_philo_must_eat)
			++i;
		if (i == phbuffer->num_of_philo)
			phbuffer->end = TRUE;
		usleep(200);
	}
	return (FALSE);
}

static void	destroy_phbuffer(t_phbuffer *phbuffer)
{
	int		i;

	i = -1;
	while (++i < phbuffer->num_of_philo)
		pthread_join(phbuffer->philo[i].thread, NULL);
	pthread_mutex_destroy(&(phbuffer->eating));
	pthread_mutex_destroy(&(phbuffer->writing));
	i = -1;
	while (++i < phbuffer->num_of_philo)
		pthread_mutex_destroy(&(phbuffer->fork[i]));
	free(phbuffer->fork);
	free(phbuffer->philo);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	phbuffer_init(&phbuffer);
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	start_routine(&phbuffer);
	destroy_phbuffer(&phbuffer);
	return (EXIT_SUCCESS);
}
