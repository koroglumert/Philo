/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_check_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:00:35 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 16:53:37 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

static int	ft_atoi(char *str)
{
	size_t			i;
	long long int	number;
	long long int	negative;

	i = 0;
	number = 0;
	negative = 1;
	while (str && (str[i] == ' ' || (9 <= str[i] && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		number *= 10;
		number += (str[i] - '0') * negative;
		if (number > 2147483647 || number < -2147483648)
			return (-1);
		i++;
	}
	if (str[i])
		return (-1);
	return ((int )(number));
}

static int	ft_to_integer(int argc, char **argv, t_data *data)
{
	data->number_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	if (data->number_philo < 1 || data->time_die < 1
		|| data->time_eat < 1 || data->time_sleep < 1
		|| (argc == 6 && data->must_eat < 1))
		return (0);
	return (1);
}

int	ft_argument_check(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		printf("ERROR! Missing number of arguments");
	else if (!ft_to_integer(argc, argv, data))
		printf("ERROR! Argument is not integer or bigger than zero");
	else
		return (1);
	return (0);
}