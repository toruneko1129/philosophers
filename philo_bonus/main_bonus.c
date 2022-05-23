/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/23 11:03:21 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_bool	setup_rules(const int argc, char **const argv,
	t_phbuffer *const phbuffer)
{
	if (get_args(argc, argv, phbuffer))
		return (TRUE);
	if (init_semaphore(phbuffer))
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_phbuffer	phbuffer;

	memset(&phbuffer, 0, sizeof(phbuffer));
	if (setup_rules(argc, argv, &phbuffer))
		return (EXIT_FAILURE);
	sem_unlink("/philo_fork");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_counting");
	return (EXIT_SUCCESS);
}
