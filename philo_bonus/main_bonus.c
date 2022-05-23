/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/23 13:40:57 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	setup_rules(const int argc, char **const argv,
	t_phbuffer *const phbuffer)
{
	if (get_args(argc, argv, phbuffer))
		return (TRUE);
	if (phbuffer->num_of_philo == 1)
		return (FALSE);
	if (init_semaphore(phbuffer) || init_philo(phbuffer))
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	memset(&phbuffer, 0, sizeof(phbuffer));
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	if (phbuffer.num_of_philo == 1)
		return (philo_solo(&phbuffer));
	sem_unlink("/philo_fork");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_counting");
	free(phbuffer.philo);
	phbuffer.philo = NULL;
	return (EXIT_SUCCESS);
}
