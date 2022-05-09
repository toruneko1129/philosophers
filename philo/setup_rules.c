/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkawakit <hkawakit@student.42tokyo.j>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:18:37 by hkawakit          #+#    #+#             */
/*   Updated: 2022/05/09 22:09:14 by hkawakit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_args(t_phbuffer phbuffer)
{
	if (phbuffer.num_of_philo <= 0 || phbuffer.time_to_die <= 0
		|| phbuffer.time_to_eat <= 0 || phbuffer.time_to_sleep <= 0)
		return (TRUE);
	if (phbuffer.opt && phbuffer.num_of_times_each_philo_must_eat <= 0)
		return (TRUE);
	return (FALSE);
}
