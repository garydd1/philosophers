/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:02:03 by dgarizad          #+#    #+#             */
/*   Updated: 2023/06/19 19:35:13 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * @brief returns 1 if the char is a number, 0 otherwise.
 * 
 * @param str 
 * @return int 
 */
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

bool	ft_error_aux(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_is_num(argv[i]) == 0)
		{
			printf("ARGS NOT NUMERICAL\n");
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_error_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("ARG_ERROR\n");
		return (true);
	}
	argv++;
	while (*argv)
	{
		if (ft_error_aux(*argv) == true)
			return (true);
		argv++;
	}
	return (false);
}
