/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   admin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:37:46 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 18:47:03 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	hermess(t_data *data, t_philo *philo, char *msg, char *colour)
{
	pthread_mutex_lock(&data->aux_mtx);
	if (data->stop == false && philo->allowed_to_eat == true)
	{
		pthread_mutex_lock(&data->stdout_mtx);
		printf("%s%lld\tms | philosopher %d %s\033[0m\n", colour, \
		kronoss(philo->born_time), philo->id + 1, msg);
		pthread_mutex_unlock(&data->stdout_mtx);
		pthread_mutex_unlock(&data->aux_mtx);
		return ;
	}
	pthread_mutex_unlock(&data->aux_mtx);
}

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
int	hermes(t_philo *philo, char *msg, long long time)
{
	pthread_mutex_lock(&philo->data->genesis);
	if (philo->data->stop == true)
	{
		pthread_mutex_unlock(&philo->data->genesis);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->genesis);
	pthread_mutex_lock(&philo->data->stdout_mtx);
	//printf(""BLUE"| %lld ms |"YW" %d"WT" %s\n",time ,philo->id + 1, msg);
	printf("%lld ms, %d, %s\n",time ,philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->stdout_mtx);
	return (0);
}

/**
 * @brief Hypnos controls the dreams world. After eating, it helps 
 * each philosopher to have a nap. 
 * But, if a philo is sleeping too much, and is close to death by diet
 * Hypnos will break their dreams ot give them the chance of living. 
 * @param philo 
 * @param time 
 * @param action 
 * @return int 
 */
int	hypnos(t_philo *philo, long long time, int action)
{	
	if (action == TTEAT)
	{
		hermes(philo, EAT, time - philo->born_time);
		pthread_mutex_lock(&philo->data->genesis);
		philo->last_ate = time - philo->born_time;
		pthread_mutex_unlock(&philo->data->genesis);
	}
	if (action == TTSLEEP)
		hermes(philo, SLEEP, kronos() - philo->born_time);
	while (kronos() - time <= philo->atributes[action])
	{
		pthread_mutex_lock(&philo->data->genesis);
		if (philo->data->stop == true)
		{
			pthread_mutex_unlock(&philo->data->genesis);
			return (-1);
		}
		pthread_mutex_unlock(&philo->data->genesis);
	}
	if (action == TTSLEEP)
		hermes(philo, THINK, kronos() - philo->born_time);
	return (0);
}

int	nymph(t_philo *philo)
{
	long long	time;
	
	time = kronos() - philo->born_time;
	if (hypnos(philo, kronos(), TTEAT) == -1) 
	{
		pthread_mutex_unlock(&philo->data->forks[philo->frst_fork].mutex);
		pthread_mutex_unlock(&philo->data->forks[philo->scnd_fork].mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->forks[philo->frst_fork].mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->scnd_fork].mutex);
	if (hypnos(philo, kronos(), TTSLEEP) == -1)
		return (-1);
	return (0);
}

/**
 * @brief Manage the pick up of the forks with their respective mutexes.
 * Demeter is the goddess associated with fertility, agriculture and haverst.
 * 
 * @param philo 
 * @return int 
 */
int	demeter(t_philo *philo)
{
	long long	time;
	
	pthread_mutex_lock(&philo->data->forks[philo->frst_fork].mutex);
	time = kronos() - philo->born_time;
	if (time - philo->last_ate >= philo->atributes[TTDIE] + philo->last_ate)
	{
		hermes(philo, RIP, time);
	}
	if (hermes(philo, FORK, time) == -1)
		return (-1);
	pthread_mutex_lock(&philo->data->forks[philo->scnd_fork].mutex);
	time = kronos() - philo->born_time;
	if (hermes(philo, FORK, time) == -1)
		return (-1);
	if (nymph(philo) == -1)
		return (-1);
	return (0);
}

/**
 * @brief Personification of death in greek mithology.
 * Thanatos will be aware if any philosopher dies so he 
 * can guide them to the underworld.
 * @param data 
 * @return int 
 */ //CHECKPOINT
int	thanatos(t_data *data)
{
	int			i;
	long long	time;
	
	while (42)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			time = kronos() - data->born_time;
			pthread_mutex_lock(&data->genesis);
			if ((kronos() - data->born_time) - data->philos[i].last_ate >= data->atributes[TTDIE])
			{
				pthread_mutex_lock(&data->aux_mtx);
				data->stop = true;
				pthread_mutex_unlock(&data->aux_mtx);
				pthread_mutex_lock(&data->stdout_mtx);
				printf(""RED"| %lld ms |"YW" %d"WT" %s\n",time ,data->philos[i].id + 1, RAP);
				pthread_mutex_unlock(&data->genesis);
				return (1);
			}
			pthread_mutex_unlock(&data->genesis);
			i++;
		}
	}
	return (0);
}

static bool	nymphh(t_data *data)
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
			return ( true);
		}
		i++;
	}
	return (false);
}

void	thanatoss(t_data *data)
{
	int	i;
	long long	time;

	while (true)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->aux_mtx);
			time = kronoss(data->philos[i].born_time);
			if (nymphh(data) == true)
				return ;
			if (time - \
			data->philos[i].last_ate >= data->atributes[TTDIE] && data->stop == false)
			{
				pthread_mutex_lock(&data->stdout_mtx);
				printf("\033[1;31m%lld\tms | philosopher %d died. Rip.*************\n", \
				time, data->philos[i].id + 1);
				pthread_mutex_unlock(&data->stdout_mtx);
				pthread_mutex_lock(&data->genesis);
				data->stop = true;
				pthread_mutex_unlock(&data->genesis);
				pthread_mutex_unlock(&data->aux_mtx);
				return ;
			}
			pthread_mutex_unlock(&data->aux_mtx);
			i++;
		}
	}
}
