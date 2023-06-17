/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:09:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/17 17:20:06 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Yes, Kronos, not Khronos or Chronos, is
 * the Titan related with the passage of time understood
 * as cycles, seasons and objective measuring of it.
 * Returns the time in ms since the begining of existence.
 * @return long	long 
 */
long	long	kronos(void)
{
	t_time time;

	gettimeofday(&time, NULL);	
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

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
long	long	kronoss(long long born_time)
{
	t_time time;

	gettimeofday(&time, NULL);	
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - born_time);
}

bool	my_usleep(long long sleep_time, t_philo *philo)
{
	long long	sleep_start;
	long long	cur_time;

	sleep_start = kronoss(philo->born_time);
	cur_time = sleep_start;
	while (cur_time - sleep_start < sleep_time)
	{
		if (stop_check(philo->data))
			return (false);
		cur_time = kronoss(philo->born_time);
	}
	return (true);
}