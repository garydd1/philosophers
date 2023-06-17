/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:07 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/17 00:41:50 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Receives an specific philosopher struct
 * which has access to the main data through philo->data.
 * For Heraclitus, phisis represents the dynamic changing of reality.
 * @param arg 
 * @return void* 
 */
void	*physis(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->data->genesis);
	while (philo->data->end == false)
	{
	}
	pthread_mutex_unlock(&philo->data->genesis);
	philo->born_time = kronos();
	if ((philo->id + 1) % 2 == 0)
	{
		hermes(philo, THINK, kronos() - philo->born_time);
		usleep(84);
	}
	while (42)
	{
		pthread_mutex_lock(&philo->data->aux_mtx);
		if (philo->data->stop == true)
		{
			pthread_mutex_unlock(&philo->data->aux_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->data->aux_mtx);
		if (demeter(philo) == - 1)
		{
			// printf("ERROR Philo: %d\n", philo->id);
			break ;
		}
	}
	return(NULL);
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * number_of_philosophers, time_to_die, time_to_eat
 * time_to_sleep,
 * [number_of_times_each_philosopher_must_eat]
 * @return int 
 */
int	main(int argc, char **argv)
{	
	t_data		data;
	int			i;

	if (argc < 5 || argc > 6)
	{
		printf("ARG_ERROR\n");
		return (1);
	}
	i = 0;
	init(&data, argc, argv);
	thanatos(&data);
	while (i < data.philo_nbr)
	{
		pthread_join(data.philos[i].tid, NULL);
		i++;
	}
	// morgan_freeman(&data);
	pthread_mutex_unlock(&data.stdout_mtx);
	return (0);
}
