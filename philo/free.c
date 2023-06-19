/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:18:03 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 19:45:36 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	morgan_freeman(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->genesis);
	pthread_mutex_destroy(&data->aux_mtx);
	pthread_mutex_destroy(&data->stdout_mtx);
	free(data->forks);
	free(data->philos);
	return (0);
}
