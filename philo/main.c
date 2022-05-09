/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/09 23:46:03 by hkawakit         ###   ########.fr       */
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
}

static t_bool	get_args(int argc, char **argv, t_phbuffer *phbuffer)
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
	if (check_args(*phbuffer))
		return (print_error(EVAL));
	return (FALSE);
}

static t_bool	init_mutex(t_phbuffer *phbuffer)
{
	int		i;

	if (pthread_mutex_init(&(phbuffer->eating), NULL)
		|| pthread_mutex_init(&(phbuffer->writing), NULL))
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
			return (print_error(EMUTEX));
		}
	}
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	phbuffer_init(&phbuffer);
	if (get_args(argc, argv, &phbuffer) || init_mutex(&phbuffer))
		return (EXIT_FAILURE);
	free(phbuffer.fork);
	return (EXIT_SUCCESS);
}
