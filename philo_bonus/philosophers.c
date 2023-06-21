/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:07 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/21 17:46:36 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Free all allocated memory
 * And close all semaphores
 * @param data 
 * @return int 
 */
int	freelancer(t_data *data)
{
	free(data->philos);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/start");
	sem_unlink("/dead");
	sem_unlink("/ate");
	sem_close(data->forks_sem);
	sem_close(data->write_sem);
	sem_close(data->start_sem);
	sem_close(data->dead_sem);
	sem_close(data->ate_sem);
	return (0);
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

	if (ft_error_check(argc, argv) == true)
		return (1);
	i = 0;
	if (init(&data, argc, argv) == 1)
		return (printf("INIT ERRORS"), 1);
	freelancer(&data);
	return (0);
}
