/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:02:03 by dgarizad          #+#    #+#             */
/*   Updated: 2023/05/07 14:28:40 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief Creates a new node with the int value passed as parameter. 
 * 
 * @param num 
 * @return t_data* 
 */
// t_data	*ft_lstnew(int num)
// {
// 	t_data	*new_node;

// 	new_node = malloc(sizeof(t_data));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->philos->id  = num;
// 	new_node->philos->next = NULL;
// 	new_node->philos->previous = NULL;
// 	return (new_node);
// }

static int	ft_is_num(char str)
{
	int	flag;

	flag = 1;
	if (str < 48 || str > 57)
		flag = 0;
	return (flag);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	digit;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
	{
		str++;
	}
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign *= -1;
		str++;
	}
	while (ft_is_num(str[i]) == 1)
	{
		digit = str[i++] - '0';
		number = (number * 10) + digit;
	}
		number = number * sign;
	return (number);
}
