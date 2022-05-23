/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/23 22:44:18 by hkawakit         ###   ########.fr       */
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

static t_bool	start_routine(t_phbuffer *const phbuffer)
{
	t_philo *const	philo = phbuffer->philo;
	int				i;
	int				wstatus;

	i = -1;
	while (++i < phbuffer->num_of_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			return (print_error(EFORK));
		else if (philo[i].pid == 0)
			philo_routine(&(philo[i]));
	}
	i = -1;
	while (++i < phbuffer->num_of_philo)
		waitpid(-1, &wstatus, 0);
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
	if (start_routine(&phbuffer))
		return (EXIT_FAILURE);
	sem_unlink("/philo_fork");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_counting");
	free(phbuffer.philo);
	phbuffer.philo = NULL;
	return (EXIT_SUCCESS);
}
