/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:54:48 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/20 12:58:08 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_death(t_phbuffer *const phbuffer, t_philo *const philo)
{
	int		i;

	i = -1;
	while (++i < phbuffer->num_of_philo)
	{
		pthread_mutex_lock(&(phbuffer->eating));
		if (get_timestamp() - philo[i].last_meal
			> (unsigned long)phbuffer->time_to_die)
		{
			print_action(phbuffer, philo[i].id, PDIED);
			pthread_mutex_lock(&(phbuffer->checker));
			phbuffer->end = TRUE;
			pthread_mutex_unlock(&(phbuffer->checker));
		}
		pthread_mutex_unlock(&(phbuffer->eating));
	}
}

void	monitor_full(t_phbuffer *const phbuffer, t_philo *const philo)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&(phbuffer->counting));
	while (phbuffer->opt && i < phbuffer->num_of_philo
		&& philo[i].cnt_ate >= phbuffer->num_of_times_each_philo_must_eat)
		++i;
	pthread_mutex_unlock(&(phbuffer->counting));
	if (i == phbuffer->num_of_philo)
	{
		pthread_mutex_lock(&(phbuffer->checker));
		phbuffer->end = TRUE;
		pthread_mutex_unlock(&(phbuffer->checker));
	}
}
