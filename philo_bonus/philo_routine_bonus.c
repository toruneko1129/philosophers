/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:05 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/26 22:25:59 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_solo(t_phbuffer *const phbuffer)
{
	const unsigned long	std = get_timestamp();
	unsigned long		res;

	while (1)
	{
		res = get_timestamp();
		if (res - std >= (unsigned long)phbuffer->time_to_die)
			break ;
		usleep(100);
	}
	printf("%lu %d %s\n", res, 1, PDIED);
	return (EXIT_SUCCESS);
}

static void	philo_wait(const unsigned long time)
{
	const unsigned long	std = get_timestamp();

	while (1)
	{
		if (get_timestamp() - std >= time)
			return ;
		usleep(100);
	}
}

static void	philo_eating(t_philo *const philo, t_phbuffer *const phbuffer)
{
	if (philo->id % 2)
		usleep(3000);
	sem_wait(phbuffer->fork);
	print_action(phbuffer, philo->id, PFORK);
	sem_wait(phbuffer->fork);
	print_action(phbuffer, philo->id, PFORK);
	print_action(phbuffer, philo->id, PEAT);
	sem_wait(phbuffer->eating);
	philo->last_meal = get_timestamp();
	sem_post(phbuffer->eating);
	philo_wait(phbuffer->time_to_eat);
	sem_post(phbuffer->fork);
	sem_post(phbuffer->fork);
	sem_wait(phbuffer->eating);
	++(philo->cnt_ate);
	sem_post(phbuffer->eating);
}

void	philo_routine(t_philo *const philo)
{
	t_phbuffer *const	phbuffer = philo->phbuffer;

	philo->last_meal = get_timestamp();
	pthread_create(&(philo->monitor), NULL, monitor_philo, philo);
	while (1)
	{
		philo_eating(philo, phbuffer);
		print_action(phbuffer, philo->id, PSLEEP);
		philo_wait(phbuffer->time_to_sleep);
		print_action(phbuffer, philo->id, PTHINK);
		usleep(100);
	}
	exit(0);
}
