/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:55:31 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 02:19:09 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_fork_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	return (0);
}

long long	ft_milisec(long long first)
{
	struct timeval	tv;
	long long		rtn;

	gettimeofday(&tv, NULL);
	rtn = (tv.tv_sec * 1000) + (tv.tv_usec / 1000)  - first;
	return (rtn);
}

static t_philo	*ft_philo_struct(t_philo *philos, t_data *data)
{
	int		i;
	t_philo	*first_philo;

	i = 1;
	philos = malloc(sizeof(t_philo));
	if (!philos)
		return (0);
	first_philo = philos;
	while (i < data->number_philo)
	{
		philos->next = malloc(sizeof(t_philo));
		if (!(philos->next))
			return (0);
		philos = philos->next;
		if (data->number_philo == (i + 1))
			philos->next = 0;
		i++;
	}
	return (first_philo);
}

static void	ft_initial(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int				i;

	i = 0;
	while (i < data->number_philo)
	{
		philos->id_philo = i + 1;
		philos->last_eat_time = ft_milisec(0);
		philos->eat_count = 0;
		philos->data = data;
		philos->fork_right = &forks[i];
		if (data->number_philo != 1 && i != 0)
			philos->fork_left = &forks[i - 1];
		else if (data->number_philo != 1)
			philos->fork_left = &forks[data->number_philo - 1];
		philos = philos->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_data			*data;
	t_philo			*philos;

	philos = 0;
	forks = 0;
	data = malloc(sizeof(t_data));
	if (!ft_argument_check(argc, argv, data))
		return (-1);
	if (!ft_mutex_init(data, &forks))
		return (0);
	philos = ft_philo_struct(philos, data);
	ft_initial(philos, data, forks);
	data->start_time = ft_milisec(0);
	ft_create_join_threads(philos);
	ft_destroy_mutex(data, forks);
	return (0);
}
