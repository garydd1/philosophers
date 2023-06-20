/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:43:39 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/20 16:48:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	zeus(data);
	return (0);
}
