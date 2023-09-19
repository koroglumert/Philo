/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:22:54 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 13:25:17 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	ft_is_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_race);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->data_race);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_race);
	return (0);
}

static int	ft_waiting_time(long long wait_time, t_philo *philo)
{
	long long	start_time;

	start_time = ft_milisec(0);
	while (ft_milisec(0) < start_time + wait_time)
	{
		if (ft_is_died(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

static int	ft_print(char *str, t_philo *philo)
{
	if (ft_is_died(philo))
		return (0);
	pthread_mutex_lock(&philo->data->printing);
	if (!ft_is_died(philo))
	{
		printf("%lld %d %s\n", ft_milisec(philo->data->start_time),
			philo->id_philo, str);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->printing);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->printing);
	return (1);
}

static int	ft_eating(t_philo *philo)
{
	if (ft_is_died(philo))
		return (0);
	pthread_mutex_lock(philo->fork_right);
	if (philo->data->number_philo == 1 || !ft_print("has taken a fork", philo))
		return (pthread_mutex_unlock(philo->fork_right));
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(&philo->data->data_race);
	philo->last_eat_time = ft_milisec(0);
	pthread_mutex_unlock(&philo->data->data_race);
	if (!ft_print("has taken a fork", philo))
		return (ft_fork_mutex_unlock(philo));
	if (!ft_print("is eating", philo))
		return (ft_fork_mutex_unlock(philo));
	if (!ft_waiting_time(philo->data->time_eat, philo))
		return (ft_fork_mutex_unlock(philo));
	ft_fork_mutex_unlock(philo);
	pthread_mutex_lock(&philo->data->data_race);
	philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		return (pthread_mutex_unlock(&philo->data->data_race));
	pthread_mutex_unlock(&philo->data->data_race);
	return (1);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (!ft_eating(philo))
			break ;
		if (!ft_print("is slepping", philo))
			break ;
		if (!ft_waiting_time(philo->data->time_sleep, philo))
			break ;
		if (!ft_print("is thinking", philo))
			break ;
	}
	return (0);
}
