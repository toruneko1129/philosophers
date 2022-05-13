/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:05 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/13 22:17:26 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//need to make solo part
static void	philo_eating(t_philo *philo)
{
	t_phbuffer	*phbuffer;

	phbuffer = philo->phbuffer;
	if (philo->id % 2)
		usleep(200);
	pthread_mutex_lock(&(phbuffer->fork[philo->left_fork]));
	//print_action(phbuffer, philo->id, "left");
	print_action(phbuffer, philo->id, PFORK);
	pthread_mutex_lock(&(phbuffer->fork[philo->right_fork]));
	//print_action(phbuffer, philo->id, "right");
	print_action(phbuffer, philo->id, PFORK);
	sleep(1);
	pthread_mutex_unlock(&(phbuffer->fork[philo->left_fork]));
	pthread_mutex_unlock(&(phbuffer->fork[philo->right_fork]));
	sleep(1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_timestamp();
	while (1)
		philo_eating(philo);
	return (NULL);
}
