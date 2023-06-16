/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:59:52 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/14 17:39:05 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	if ((i + 1) % 2 == 0)
	{
		data->philos[i].frst_fork = i + 1;
		data->philos[i].scnd_fork = i;
	}
	else
	{
		data->philos[i].frst_fork = i;
		data->philos[i].scnd_fork = i + 1;
	}
	if (i == data->philo_nbr - 1)
	{
		data->philos[i].frst_fork = 0;
		if ((i + 1) % 2 != 0)
			data->philos[i].scnd_fork = i;
	}
	printf("\nphilo:%d first fork: %d, second:%d\n", i+1, data->philos[i].frst_fork +1, data->philos[i].scnd_fork +1);
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
			j++;
		}
		i++;
	}
	return (0);
}

//CHECKPOINT
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
	data->philos = malloc(sizeof(t_philo) * data->philo_nbr); //NEED FREE
	memset(data->philos, 0, sizeof(t_philo));
	epimetheus(data);
	pthread_mutex_init(&data->genesis, NULL);
	pthread_mutex_lock(&data->genesis);
	while (data->i < data->philo_nbr)
	{
		if (pthread_create(&thread_id, NULL, physis, \
		&data->philos[data->i]) != 0)
			return (1);
		printf("\nborn thread id: %lu . FILOSOFO SALVAJE APARECE: %d \n", (unsigned long)thread_id, data->i + 1);
		usleep(1);
		data->philos[data->i].tid = (thread_id);
		(data->i)++;
		pthread_detach(thread_id);
	}
	data->end = true;
	data->born_time = kronos();
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
	printf("\nthere are %d philos\n", data->philo_nbr);
	create_forks(data);
	pthread_mutex_init(&data->stdout_mtx, NULL);
	prometeus(data);
	return (0);
}
