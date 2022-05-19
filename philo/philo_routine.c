/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:05 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/16 17:47:35 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_wait(t_phbuffer *const phbuffer, const unsigned long time)
{
	const unsigned long	std = get_timestamp();

	while (1)
	{
		pthread_mutex_lock(&(phbuffer->checker));
		if (phbuffer->end)
		{
			pthread_mutex_unlock(&(phbuffer->checker));
			return ;
		}
		pthread_mutex_unlock(&(phbuffer->checker));
		if (get_timestamp() - std >= time)
			return ;
		usleep(100);
	}
}

int	philo_solo(t_phbuffer *const phbuffer)
{
	philo_wait(phbuffer, phbuffer->time_to_die);
	printf("%lu %d %s\n", get_timestamp(), 1, PDIED);
	return (EXIT_SUCCESS);
}

static void	philo_eating(t_philo *const philo, t_phbuffer *const phbuffer)
{
	if (philo->id % 2)
		usleep(7000);
	pthread_mutex_lock(&(phbuffer->fork[philo->left_fork]));
	print_action(phbuffer, philo->id, PFORK);
	pthread_mutex_lock(&(phbuffer->fork[philo->right_fork]));
	print_action(phbuffer, philo->id, PFORK);
	print_action(phbuffer, philo->id, PEAT);
	pthread_mutex_lock(&(phbuffer->eating));
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&(phbuffer->eating));
	philo_wait(phbuffer, phbuffer->time_to_eat);
	pthread_mutex_lock(&(phbuffer->counting));
	++(philo->cnt_ate);
	pthread_mutex_unlock(&(phbuffer->counting));
	pthread_mutex_unlock(&(phbuffer->fork[philo->right_fork]));
	pthread_mutex_unlock(&(phbuffer->fork[philo->left_fork]));
}

void	*philo_routine(void *arg)
{
	t_philo *const		philo = (t_philo *)arg;
	t_phbuffer *const	phbuffer = philo->phbuffer;

	while (1)
	{
		pthread_mutex_lock(&(phbuffer->checker));
		if (phbuffer->end)
		{
			pthread_mutex_unlock(&(phbuffer->checker));
			return (NULL);
		}
		pthread_mutex_unlock(&(phbuffer->checker));
		philo_eating(philo, phbuffer);
		print_action(phbuffer, philo->id, PSLEEP);
		philo_wait(phbuffer, phbuffer->time_to_sleep);
		print_action(phbuffer, philo->id, PTHINK);
		usleep(100);
	}
	return (NULL);
}

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
	if (phbuffer->end)
		return ;
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
	usleep(100);
}
