/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cerberus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:26:53 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/20 21:50:55 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*cerberus(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	sem_wait(data->dead_sem);
	i = 0;
	while (i < data->philo_nbr)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	sem_post(data->write_sem);
	return (0);
}

/**
 * @brief Cerberus is the guardian of the underworld.
 * It waits for all philosophers to have eaten the
 * number of times specified in the arguments.
 * @param data 
 * @return int 
 */
void	*orthrus(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	i = 0;
	while (i < data->philo_nbr)
	{
		sem_wait(data->ate_sem);
		i++;
	}
	sem_wait(data->write_sem);
	printf("All philosophers ate %d times\n", data->philo_nbr);
	i = 0;
	while (i < data->philo_nbr)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
	sem_post(data->write_sem);
	return (0);
}

/**
 * @brief Hydra is one of the heads of Cerberus.
 * This thread is called by each philosopher.
 * It checks if the philosopher is dead.
 * @param arg 
 * @return void* 
 */
void	*hydra(void *arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)arg;
	while (42)
	{
		time = aion(philo->born_time);
		if (time - philo->last_ate >= philo->atributes[TTDIE])
		{
			sem_wait(philo->data->write_sem);
			printf(RED"%lld %d died"RST"\n", time, philo->id + 1);
			sem_post(philo->data->dead_sem);
			return (0);
		}
	}
	return (0);
}
