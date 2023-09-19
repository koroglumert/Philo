/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:22:54 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 16:53:15 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

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

static int	ft_eating(t_philo *philo, t_data *data)
{
	if (ft_is_died(philo))
		return (0);
	sem_wait(data->semaphore);
	if (data->number_philo == 1 || !ft_print("has taken a fork", philo))
	{
		sem_post(data->semaphore);
		return (0);
	}
	sem_wait(data->semaphore);
	pthread_mutex_lock(&data->data_race);
	philo->last_eat_time = ft_milisec(0);
	pthread_mutex_unlock(&data->data_race);
	if (!ft_print("has taken a fork", philo))
		return (ft_fork_semaphore_post(data));
	if (!ft_print("is eating", philo))
		return (ft_fork_semaphore_post(data));
	if (!ft_waiting_time(data->time_eat, philo))
		return (ft_fork_semaphore_post(data));
	ft_fork_semaphore_post(data);
	pthread_mutex_lock(&data->data_race);
	philo->eat_count += 1;
	if (philo->eat_count == philo->data->must_eat)
		return (pthread_mutex_unlock(&data->data_race));
	pthread_mutex_unlock(&data->data_race);
	return (1);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (!ft_eating(philo, philo->data))
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
