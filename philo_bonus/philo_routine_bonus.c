/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:00:05 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/24 00:38:49 by hkawakit         ###   ########.fr       */
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

void	philo_routine(t_philo *const philo)
{
	t_phbuffer *const	phbuffer = philo->phbuffer;

	philo->last_meal = get_timestamp();
	exit(0);
}
