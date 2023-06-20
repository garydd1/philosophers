/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:32:50 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/20 18:13:49 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Returns the time in ms since the 
 * begining of the simulation.
 * Aion is the god that represents time here. 
 * represents the circular and infinite time.
 * Returns the time in ms since the begining of existence.
 * @param born_time 
 * @return long	long 
 */
long	long	aion(long long born_time)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - born_time);
}

	bool	hypnos(long long sleep_time, t_philo *philo)
	{
		long long	sleep_start;
		long long	cur_time;

		sleep_start = aion(philo->born_time);
		cur_time = sleep_start;
		while (cur_time - sleep_start < sleep_time)
		{
			// if (stop_check(philo->data))
			// 	return (false);
			cur_time = aion(philo->born_time);
		}
		return (true);
	}
