/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/09 12:55:13 by hkawakit         ###   ########.fr       */
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
}

static int	setup_rules(int argc, char **argv, t_phbuffer *phbuffer)
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	phbuffer_init(&phbuffer);
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
