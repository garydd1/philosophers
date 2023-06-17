/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:03:07 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/17 17:43:23 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	stop_check(t_data *data)
{
	pthread_mutex_lock(&data->aux_mtx);
	if (data->stop == true)
	{
		pthread_mutex_unlock(&data->aux_mtx);
		return (true);
	}
	pthread_mutex_unlock(&data->aux_mtx);
	return (false);
}

static void	pick_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id].mutex);
	hermess(philo->data, philo, "took a fork", "");
	if (data->philo_nbr == 1)
	{
		philo->allowed_to_eat = false;
		return ;
	}
	if (philo->id + 1 == data->philo_nbr)
		pthread_mutex_lock(&data->forks[0].mutex);
	else
		pthread_mutex_lock(&data->forks[philo->id + 1].mutex);
	hermess(philo->data, philo, "took another fork", "");
}

static bool	eat(t_philo *philo, t_data *data)
{
	int64_t	cur_time;

	pick_forks(philo, data);
	pthread_mutex_lock(&data->aux_mtx);
	if (data->stop == false && philo->allowed_to_eat == true)
	{
		philo->eat_count++;
		cur_time = kronoss(philo->born_time);
		philo->last_ate = cur_time;
		printf("%lld\tms | philosopher %d is eating\n", \
		kronoss(philo->born_time), philo->id + 1);
		pthread_mutex_unlock(&data->aux_mtx);
		if (my_usleep(philo->atributes[TTEAT], philo) == false)
			return (unpick_forks(philo, data), \
			pthread_mutex_unlock(&data->aux_mtx), false);
	}
	else
		pthread_mutex_unlock(&data->aux_mtx);
	unpick_forks(philo, data);
	return (true);
}

/**
 * @brief Receives an specific philosopher struct
 * which has access to the main data through philo->data.
 * For Heraclitus, physis represents the dynamic changing of reality.
 * @param arg 
 * @return void* 
 */
void	*physis(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if ((philo->id) % 2 == 1)
	{
		//hermes(philo, THINK, 0);
		my_usleep(20, philo);
	}
	while (philo->eat_count < philo->atributes[MUST_EAT] ||
	philo->atributes[MUST_EAT] == MAX_EAT)
	{
		if (stop_check(philo->data) == true)
			break ;
		if (eat(philo, philo->data) == false)
			return (NULL);
		hermess(philo->data, philo, "is sleeping", "");
		if (my_usleep(philo->atributes[TTSLEEP], philo) == false)
			return (NULL);
		hermess(philo->data, philo, "is thinking", "");
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

	if (ft_error_check(argc, argv) == true)
		return (1);
	i = 0;
	if (init(&data, argc, argv) == 1)
		return (printf("INIT ERRORS"), 1);
	//thanatos(&data);
	thanatoss(&data);
	while (i < data.philo_nbr)
	{
		pthread_join(data.philos[i].tid, NULL);
		i++;
	}
	// morgan_freeman(&data);
	pthread_mutex_unlock(&data.stdout_mtx);
	return (0);
}
