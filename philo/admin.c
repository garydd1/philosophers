/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/21 20:14:55 by dgarizad         ###   ########.fr       */
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
	pthread_mutex_lock(&data->aux_mtx);
	if (data->stop == false && philo->allowed_to_eat == true)
	{
		pthread_mutex_lock(&data->stdout_mtx);
		printf("%s%lld\tms | philosopher %d %s\n", color, \
		kronos(philo->born_time), philo->id + 1, msg);
		pthread_mutex_unlock(&data->stdout_mtx);
		pthread_mutex_unlock(&data->aux_mtx);
		return ;
	}
	pthread_mutex_unlock(&data->aux_mtx);
}

/**
 * @brief Nymphs, daughters of Zeus, goddesses of nature.
 * Here they are the ones who will check if all the philosophers
 * have eaten the required amount of times.
 * @param data 
 * @return true 
 * @return false 
 */
static bool	nymph(t_data *data)
{
	int	i;
	int	meals_needed;

	i = 0;
	meals_needed = data->philo_nbr;
	while (i < data->philo_nbr)
	{
		if (data->philos[i].eat_count == data->atributes[MUST_EAT])
			meals_needed--;
		if (meals_needed <= 0)
		{
			pthread_mutex_lock(&data->genesis);
			data->stop = true;
			pthread_mutex_unlock(&data->genesis);
			pthread_mutex_unlock(&data->aux_mtx);
			pthread_mutex_lock(&data->stdout_mtx);
			printf("All Phils have eaten!\n");
			pthread_mutex_unlock(&data->stdout_mtx);
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * @brief Moros, son of Nyx, god of doom.
 * Here he is the one who will kill the philosophers if
 * they don't eat in time.
 * 
 * @param data 
 * @param i 
 * @param time 
 */
void	moros(t_data *data, int i, long long time)
{
	pthread_mutex_lock(&data->stdout_mtx);
	printf("\033[1;31m%lld\tms | philosopher %d died.\n", \
	time, data->philos[i].id + 1);
	pthread_mutex_unlock(&data->stdout_mtx);
	pthread_mutex_lock(&data->genesis);
	data->stop = true;
	pthread_mutex_unlock(&data->genesis);
	pthread_mutex_unlock(&data->aux_mtx);
}

/**
 * @brief Personification of death in greek mithology.
 * Thanatos will be aware if any philosopher dies so he 
 * can guide them to the underworld.
 * @param data 
 * @return int 
 */
void	thanatos(t_data *data)
{
	int			i;
	long long	time;

	while (true)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->aux_mtx);
			time = kronos(data->philos[i].born_time);
			if (nymph(data) == true)
				return ;
			if (time - data->philos[i].last_ate >= \
			data->atributes[TTDIE] && data->stop == false)
			{
				moros(data, i, time);
				return ;
			}
			pthread_mutex_unlock(&data->aux_mtx);
			i++;
		}
	}
}
