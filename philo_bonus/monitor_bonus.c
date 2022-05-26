/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:23:02 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/26 22:54:06 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_philo(void *arg)
{
	t_philo *const		philo = (t_philo *)arg;
	t_phbuffer *const	phbuffer = philo->phbuffer;

	while (1)
	{
		sem_wait(phbuffer->eating);
		if (get_timestamp() - philo->last_meal
			> (unsigned long)phbuffer->time_to_die)
		{
			print_action(phbuffer, philo->id, PDIED);
			exit(1);
		}
		if (philo->cnt_ate >= phbuffer->num_of_times_each_philo_must_eat)
		{
			sem_post(phbuffer->eating);
			exit(0);
		}
		sem_post(phbuffer->eating);
		usleep(100);
	}
	return (NULL);
}
