/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:36:59 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/09 00:53:39 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"
//bununla ilgili düzenlemeler lazım olabilir. eat konusunda kontrol yetersiz kalıyor
void	*ft_dead_thread(void *arg)
{
	t_philo *tmp;
	t_philo *philo;

	philo = arg;
	tmp = philo;
	while (1)
	{
		if (ft_milisec(philo->last_eat_time) >= philo->data->time_die
			&& philo->eat_count != philo->data->must_eat)
		{
			philo->data->is_dead = 1;
			pthread_mutex_lock(&philo->data->printing);
			printf("%ld- %d. Philo is Dead!",
			ft_milisec(philo->data->start_time), philo->id_philo);
			pthread_mutex_unlock(&philo->data->printing);
			return (0);
		}
		philo = philo->next;
		if (!philo)
			philo = tmp;
	}
	return (0);
}

int	ft_mutex_init(t_data *data, pthread_mutex_t	*forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->printing, NULL))
		return (0);
	forks = malloc (sizeof(pthread_mutex_t) * data->number_philo);
	if (!forks)
		return (0);
	while (i < data->number_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

void	ft_create_join_threads(t_philo *philos)
{
	t_philo *tmp;
	tmp = philos;

	while (philos)
	{
		printf("X\n");
		fflush(stdout);
		if (philos->id_philo % 2 == 0)
			usleep(10);
		pthread_create(&(philos->id_thread), NULL, ft_thread_function, philos);
		
		philos = philos->next;
	}
	//pthread_create(&(philos->data->id_dead_thread), NULL, ft_dead_thread, tmp);
	while (tmp)
	{
		printf("Z\n");
		fflush(stdout);
		pthread_join(tmp->id_thread, NULL);
		tmp = tmp->next;
	}
	printf("M\n");
		fflush(stdout);
	
}

void	ft_destroy_mutex(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->printing);
	while (i < data->number_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}