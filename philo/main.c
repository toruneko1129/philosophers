/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/10 16:12:47 by hkawakit         ###   ########.fr       */
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
	int		i;

	if (get_args(argc, argv, phbuffer) || init_mutex(phbuffer))
		return (TRUE);
	phbuffer->philo = (t_philo *)malloc(sizeof(t_philo)
			* phbuffer->num_of_philo);
	//move to init_philo
	if (phbuffer->philo == NULL)
	{
		free(phbuffer->fork);
		return (print_error(EMALLOC));
	}
	i = -1;
	while (++i < phbuffer->num_of_philo)
		init_philo(&(phbuffer->philo[i]), i);
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	phbuffer_init(&phbuffer);
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	free(phbuffer.fork);
	free(phbuffer.philo);
	return (EXIT_SUCCESS);
}
