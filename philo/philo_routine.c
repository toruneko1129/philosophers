/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:05 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/15 16:10:53 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_wait(t_phbuffer *phbuffer, long time)
{
	const long	std = get_timestamp();

	while (!(phbuffer->end))
	{
		if (get_timestamp() - std >= time)
			break ;
		usleep(200);
	}
}

//need to make solo part
static void	philo_eating(t_philo *philo)
{
	t_phbuffer	*phbuffer;

	phbuffer = philo->phbuffer;
	if (philo->id % 2)
		usleep(10000);
	pthread_mutex_lock(&(phbuffer->fork[philo->left_fork]));
	print_action(phbuffer, philo->id, PFORK);
	pthread_mutex_lock(&(phbuffer->fork[philo->right_fork]));
	print_action(phbuffer, philo->id, PFORK);
	pthread_mutex_lock(&phbuffer->eating);
	print_action(phbuffer, philo->id, PEAT);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&phbuffer->eating);
	philo_wait(phbuffer, phbuffer->time_to_eat);
	++(philo->cnt_ate);
	pthread_mutex_unlock(&(phbuffer->fork[philo->left_fork]));
	pthread_mutex_unlock(&(phbuffer->fork[philo->right_fork]));
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_phbuffer	*phbuffer;

	philo = (t_philo *)arg;
	phbuffer = philo->phbuffer;
	philo->last_meal = get_timestamp();
	while (!phbuffer->end)
	{
		philo_eating(philo);
		print_action(phbuffer, philo->id, PSLEEP);
		philo_wait(phbuffer, phbuffer->time_to_sleep);
		print_action(phbuffer, philo->id, PTHINK);
		usleep(200);
	}
	return (NULL);
}
