/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   olimpus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:43:54 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/21 17:12:14 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Hades is the god of the underworld.
 * will release Cerberus Thread.
 * Also, Orthrus will be released for
 * checking if a philosopher has died.
 * 
 * @param data 
 * @return true 
 * @return false 
 */
bool	hades(t_data *data)
{
	if (data->argc == 6)
	{
		if (pthread_create(&(data->cerberus_th), NULL, orthrus, data) != 0)
			return (false);
	}
	if (pthread_create(&(data->orthrus_th), NULL, cerberus, data) != 0)
		return (false);
	return (true);
}

/**
 * @brief Hera is the goddess of marriage.
 * Here the philosophers will eat, sleep and think.
 * Also, Hydra will be released for checking if a
 * philosopher has died.
 * @param philo 
 * @param i 
 * @return int 
 */
int	hera(t_philo *philo, int i)
{
	if (philo->id % 2 == 1)
		usleep(10);
	sem_unlink("/eats");
	philo->eats = sem_open("/eats", O_CREAT, 0644, 1);
	if (pthread_create(&(philo->data->hydra_th), NULL, hydra, philo) != 0)
		return (printf("Error pthread create\n"), 1);
	i = 0;
	while (philo->data->stop == false || \
	philo->atributes[MUST_EAT] == MAX_EAT)
	{
		eat(philo, philo->data);
		hermes(philo->data, philo, "is sleeping", PINK);
		usleep(philo->atributes[TTSLEEP]);
		hermes(philo->data, philo, "is thinking", YW);
		if (philo->eat_count == philo->atributes[MUST_EAT])
			sem_post(philo->data->ate_sem);
	}
	return (0);
}

/**
 * @brief Athena is the goddess of wisdom.
 * Here the variables of the philosophers will be initialized.
 * @param data 
 * @param i 
 * @return int 
 */
int	athena(t_data *data, int i)
{
	data->philos[i].id = i;
	data->philos[i].data = data;
	data->philos[i].born_time = data->born_time;
	data->philos[i].alive = true;
	data->philos[i].allowed_to_eat = true;
	return (0);
}

/**
 * @brief Create the philosophers and its pids
 * 
 * @param data 
 * @return int 
 */
int	poseidon(t_data *data)
{
	int	i;
	int	j;

	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (data->philos == NULL)
		return (1);
	memset(data->philos, 0, sizeof(t_philo) * data->philo_nbr);
	i = 0;
	while (i < data->philo_nbr)
	{
		athena(data, i);
		j = 0;
		while (j < data->argc - 2)
		{
			data->philos[i].atributes[j] = data->atributes[j];
			data->philos[i].atributes[MUST_EAT] = data->atributes[MUST_EAT];
			j++;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Each philosopher is a process. 
 * 
 * @param data 
 * @return int 
 */
int	zeus(t_data *data)
{
	int	i;

	i = 0;
	poseidon(data);
	data->born_time = aion(0);
	while (i < data->philo_nbr)
	{
		data->philos[i].pid = fork();
		data->philos[i].born_time = data->born_time;
		if (data->philos[i].pid == 0)
		{
			hera(&data->philos[i], i);
			exit(0);
		}
		i++;
	}
	hades(data);
	waitpid(-1, NULL, 0);
	return (0);
}
