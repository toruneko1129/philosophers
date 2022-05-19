/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:02:07 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/16 17:12:11 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_phbuffer *const phbuffer, int id, const char *action)
{
	pthread_mutex_lock(&(phbuffer->writing));
	pthread_mutex_lock(&(phbuffer->checker));
	if (!phbuffer->end)
		printf("%lu %d %s\n", get_timestamp(), id, action);
	pthread_mutex_unlock(&(phbuffer->checker));
	pthread_mutex_unlock(&(phbuffer->writing));
}
