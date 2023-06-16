/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:09:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/12 22:30:46 by dgarizad         ###   ########.fr       */
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
