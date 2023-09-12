/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:22:54 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/12 21:21:01 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	ft_waiting_time(long long wait_time, t_philo *philo)
{
	long long	start_time;

	start_time = ft_milisec(0);
	while (ft_milisec(0) < start_time + wait_time)
	{
		if (philo->data->is_dead == 1)
			return (0);
		usleep(100);
	}
	return (1);
}

static int	ft_print(char *str, t_philo *philo)
{
	if (philo->data->is_dead == 1)
		return (0);
	pthread_mutex_lock(&philo->data->printing);
	if (philo->data->is_dead != 1)
	{
		printf("%lld %d %s\n", ft_milisec(philo->data->start_time),
			philo->id_philo, str);
	}
	pthread_mutex_unlock(&philo->data->printing);
	return (1);
}

static int	ft_eating(t_philo *philo)
{
	if (philo->data->is_dead == 1)
		return (0);
	pthread_mutex_lock(philo->fork_right);
	if (!ft_print("has taken a right fork", philo))
		return (0);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	pthread_mutex_lock(philo->fork_left);
	if (!ft_print("has taken a left fork", philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	if (!ft_print("is eating", philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	philo->last_eat_time = ft_milisec(0);
	if (!ft_waiting_time(philo->data->time_eat, philo))
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		return (0);
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
		if (!ft_print("is Slepping", philo))
			break ;
		if (!ft_waiting_time(philo->data->time_sleep, philo))
			break ;
		if (!ft_print("is Thinking", philo))
			break ;
	}
	return (0);
}
