/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:09:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 19:47:29 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Returns the time in ms since the 
 * begining of the simulation.
 * Yes, Kronos, not Khronos or Chronos, is
 * the Titan related with the passage of time understood
 * as cycles, seasons and objective measuring of it.
 * Returns the time in ms since the begining of existence.
 * @param born_time 
 * @return long	long 
 */
long	long	kronos(long long born_time)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - born_time);
}

bool	hypnos(long long sleep_time, t_philo *philo)
{
	long long	sleep_start;
	long long	cur_time;

	sleep_start = kronos(philo->born_time);
	cur_time = sleep_start;
	while (cur_time - sleep_start < sleep_time)
	{
		if (stop_check(philo->data))
			return (false);
		cur_time = kronos(philo->born_time);
	}
	return (true);
}
