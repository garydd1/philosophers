/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   earth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:45:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/21 16:58:27 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Hermes, son of Zeus, god of heralds, commerce and
 * other irrelevant things for this project.
 * Here he is the messenger of all threads to 
 * the stdout.
 * @param philo 
 * @param msg 
 * @param time 
 * @return int 
 */
void	hermes(t_data *data, t_philo *philo, char *msg, char *color)
{
	if (data->stop == false && philo->allowed_to_eat == true)
	{
		sem_wait(data->write_sem);
		printf("%s%lld\tms | philosopher %d %s"RST"\n", color, \
		aion(philo->born_time), philo->id + 1, msg);
		sem_post(data->write_sem);
		return ;
	}
}

void	unpick_forks(t_philo *philo, t_data *data)
{
	sem_post(data->forks_sem);
	hermes(data, philo, "has dropped 1 fork", "");
	if (data->philo_nbr == 1)
		return ;
	sem_post(data->forks_sem);
	hermes(data, philo, "has dropped 2 fork", "");
}

static void	pick_forks(t_philo *philo, t_data *data)
{
	sem_wait(data->forks_sem);
	hermes(data, philo, "has taken 1 fork", GREEN);
	if (data->philo_nbr == 1)
	{
		philo->allowed_to_eat = false;
		return ;
	}
	sem_wait(data->forks_sem);
	hermes(data, philo, "has taken 2 fork", BLUE);
}

bool	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	pick_forks(philo, data);
	if (data->stop == false && philo->allowed_to_eat == true)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->atributes[MUST_EAT])
			sem_post(philo->data->ate_sem);
		cur_time = aion(philo->born_time);
		sem_wait(philo->eats);
		philo->last_ate = cur_time;
		sem_post(philo->eats);
		sem_wait(data->write_sem);
		printf("%lld\tms | philosopher %d is eating\n", \
		aion(philo->born_time), philo->id + 1);
		sem_post(data->write_sem);
		hypnos(data->atributes[TTEAT], philo);
	}
	unpick_forks(philo, data);
	return (true);
}
