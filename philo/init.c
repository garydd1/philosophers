/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:59:52 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/21 17:37:23 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unpick_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->id].mutex);
	hermes(philo->data, philo, "released a fork", "");
	if (data->philo_nbr == 1)
		return ;
	if (philo->id + 1 == data->philo_nbr)
		pthread_mutex_unlock(&data->forks[0].mutex);
	else
		pthread_mutex_unlock(&data->forks[philo->id + 1].mutex);
	hermes(philo->data, philo, "released another fork", "");
}

/**
 * @brief Pandora married with epimetheus...
 * The troubles of all philosophers are released here when Pandora opens the box.
 * Here is the definition of the protocol of picking up the forks.
 * even indexed will take left fork first. Uneven will pick the right fork first.
 * 
 * @param data 
 * @param i 
 * @return int 
 */
int	pandora(t_data *data, int i)
{
	data->philos[i].id = i;
	data->philos[i].data = data;
	data->philos[i].alive = true;
	data->philos[i].allowed_to_eat = true;
	return (0);
}

/**
 * @brief Sets the id of each philosofer and sets its atributtes. 
 * If there is no MUST_EAT argument, its set to -42 to simulate infinite.
 * Epimetheus was Prometheus`s brother. After the creation of
 * humans, Zeus punished them with Pandora`s box.
 * @param data 
 * @return int 
 */
int	epimetheus(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->philo_nbr)
	{
		pandora(data, i);
		j = 0;
		while (j < data->argc - 2)
		{
			data->philos[i].atributes[j] = ft_atoi(data->argv[j + 2]);
			if (data->argc == 5)
				data->philos[i].atributes[MUST_EAT] = MAX_EAT;
			else
				data->philos[i].atributes[MUST_EAT] = ft_atoi(data->argv[5]);
			j++;
		}
		i++;
	}
	pthread_mutex_init(&data->genesis, NULL);
	return (0);
}

/**
 * @brief Creates an array of philosofers, init them and create
 * the threads for each one. 
 * The titan Prometeus created first humans with fire and clay.
 * Some other myths says it was Zeus, but who cares.
 * @param data 
 * @return int 
 */
int	prometeus(t_data *data)
{
	pthread_t	thread_id;

	data->i = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philos)
		return (1);
	memset(data->philos, 0, sizeof(t_philo));
	epimetheus(data);
	data->born_time = kronos(0);
	while (data->i < data->philo_nbr)
	{
		data->philos[data->i].born_time = data->born_time;
		if (pthread_create(&thread_id, NULL, physis, \
		&data->philos[data->i]) != 0)
			return (1);
		data->philos[data->i].tid = (thread_id);
		(data->i)++;
	}
	data->end = true;
	pthread_mutex_unlock(&data->genesis);
	return (0);
}

/**
 * @brief Initialize structural data.
 * calls the function that creates the Philosophers.
 * @param data 
 * @param argv 
 * @return int 
 */
int	init(t_data *data, int argc, char **argv)
{	
	int	i;

	memset(data, 0, sizeof(t_data));
	data->argc = argc;
	data->argv = argv;
	data->philo_nbr = ft_atoi(argv[1]);
	i = 0;
	while (i < argc - 2)
	{
		data->atributes[i] = ft_atoi(argv[i + 2]);
		i++;
	}
	if (argc == 5)
		data->atributes[MUST_EAT] = MAX_EAT;
	else
		data->atributes[MUST_EAT] = ft_atoi(argv[5]);
	if (create_forks(data) != 0)
		return (1);
	prometeus(data);
	return (0);
}
