/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:36:59 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 16:53:22 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo_bonus.h"

void	ft_destroy_mutex_semaphore(t_data *data)
{
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->data_race);
	sem_close(data->semaphore);
	sem_unlink("Semaphore_Fork");
}

static int	ft_eat_count_control(t_philo *philos)
{
	t_philo *tmp;

	tmp = philos;
	pthread_mutex_lock(&philos->data->data_race);
	while (philos)
	{
		if (philos->eat_count != philos->data->must_eat)
			return (pthread_mutex_unlock(&philos->data->data_race));
		philos = philos->next;
	}
	pthread_mutex_unlock(&tmp->data->data_race);
	return (1);
}

static void	*ft_thread_control(t_philo *philos)
{
	t_philo	*tmp;

	tmp = philos;
	while (1)
	{
		pthread_mutex_lock(&philos->data->data_race);
		if ((philos->data->must_eat == -1 || philos->eat_count != philos->data->must_eat)
			&& ft_milisec(philos->last_eat_time) > philos->data->time_die)
		{
			philos->data->is_dead = 1;
			pthread_mutex_unlock(&philos->data->data_race);
			pthread_mutex_lock(&philos->data->printing);
			printf("%lld %d is died\n",
				ft_milisec(philos->data->start_time), philos->id_philo);
			pthread_mutex_unlock(&philos->data->printing);
			return (0);
		}
		pthread_mutex_unlock(&philos->data->data_race);
		philos = philos->next;
		if (!philos && tmp->data->must_eat && ft_eat_count_control(tmp))
			return (0);
		if (!philos)
			philos = tmp;
		usleep(100);
	}
	return (0);
}

void	ft_create_join_threads(t_philo *philos)
{
	t_philo	*tmp;

	tmp = philos;
	while (philos)
	{
		if (philos->id_philo % 2 == 1)
			pthread_create(&(philos->id_thread), NULL, ft_thread, philos);
		philos = philos->next;
	}
	usleep(100);
	philos = tmp;
	while (philos)
	{
		if (philos->id_philo % 2 == 0)
			pthread_create(&(philos->id_thread), NULL, ft_thread, philos);
		philos = philos->next;
	}
	ft_thread_control(tmp);
	while (tmp)
	{
		pthread_join(tmp->id_thread, NULL);
		tmp = tmp->next;
	}
}

int	ft_init_mutex_semaphore(t_data *data)
{
	if (pthread_mutex_init(&data->printing, NULL))
		return (0);
	if (pthread_mutex_init(&data->data_race, NULL))
		return (0);
	sem_unlink("Semaphore_Fork");
	data->semaphore = sem_open("Semaphore_Fork", O_CREAT, 0644, data->number_philo);
	if (data->semaphore == SEM_FAILED)
        return (0);
	return (1);
}