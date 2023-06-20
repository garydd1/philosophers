/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:49:32 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/20 19:01:05 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Forks are
 * represented by a semaphore.
 * Also, there is a semaphore
 * for other variables.
 * @param data 
 * @return int 
 */
int create_forks(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/start");
	sem_unlink("/dead");
	sem_unlink("/ate");
    data->forks_sem = sem_open("/forks", O_CREAT, 0666, data->philo_nbr);
    data->write_sem = sem_open("/write", O_CREAT, 0666, 1);
    data->start_sem = sem_open("/start", O_CREAT, 0666, 1);
    data->dead_sem = sem_open("/dead", O_CREAT, 0666, 0);
    data->ate_sem = sem_open("/ate", O_CREAT, 0666, 0);
	if (data->forks_sem == SEM_FAILED ||
        data->write_sem == SEM_FAILED ||
        data->start_sem == SEM_FAILED ||
        data->dead_sem == SEM_FAILED ||
		data->ate_sem == SEM_FAILED)
    {
        perror("sem_open");
        return 1;
    }
    printf("Forks created: %d\n", data->philo_nbr);
    return 0;
}
