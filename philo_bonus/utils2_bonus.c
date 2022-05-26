/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:02:07 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/26 22:49:08 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && (*s1 || *s2))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		++s1;
		++s2;
	}
	return (0);
}

void	print_action(t_phbuffer *const phbuffer, const int id,
			const char *action)
{
	sem_wait(phbuffer->writing);
	printf("%lu %d %s\n", get_timestamp(), id, action);
	(void)ft_strncmp;
	if (ft_strncmp(PDIED, action, ft_strlen(PDIED)))
		sem_post(phbuffer->writing);
}
