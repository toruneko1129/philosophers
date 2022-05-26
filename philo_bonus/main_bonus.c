/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:58:03 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/26 23:39:18 by hkawakit         ###   ########.fr       */
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
	{
		waitpid(-1, &wstatus, 0);
		if (WEXITSTATUS(wstatus))
		{
			i = -1;
			while (++i < phbuffer->num_of_philo)
				kill(philo[i].pid, SIGKILL);
			break ;
		}
	}
	return (FALSE);
}

static void	destroy_phbuffer(t_phbuffer *const phbuffer)
{
	sem_unlink("/philo_fork");
	sem_unlink("/philo_eating");
	sem_unlink("/philo_writing");
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
	if (start_routine(&phbuffer))
		return (EXIT_FAILURE);
	destroy_phbuffer(&phbuffer);
	return (EXIT_SUCCESS);
}
