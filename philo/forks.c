/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:49:32 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 20:38:15 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (1);
	while (i < data->philo_nbr)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].mutex, NULL))
		{
			printf("error mutex init\n");
			return (1);
		}
		i++;
	}
	return (0);
}
