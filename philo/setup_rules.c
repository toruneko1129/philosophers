/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:18:37 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/09 11:50:54 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_phbuffer phbuffer)
{
	if (phbuffer.num_of_philo <= 0)
		return (1);
	if (phbuffer.time_to_die <= 0)
		return (1);
	if (phbuffer.time_to_eat <= 0) 
		return (1);
	if (phbuffer.time_to_sleep <= 0)
		return (1);
	if (phbuffer.opt && phbuffer.num_of_times_each_philo_must_eat <= 0)
		return (1);
	return (0);
}
