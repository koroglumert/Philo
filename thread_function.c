/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:22:54 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/06 21:44:53 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	ft_print(char *str, t_philo *philo)
{
	if (philo->data->is_dead == 1)
		return (0);
	pthread_mutex_lock(&philo->data->printing);
	printf("%ld- %d. %s", ft_milisec(philo->data->start_time),
		philo->id_philo, str);
	pthread_mutex_unlock(&philo->data->printing);
	return (1);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	if (ft_print("took the right fork", philo))
		return (0);
	pthread_mutex_lock(philo->fork_left);
	if (ft_print("took the right fork", philo))
		return (0);
	philo->last_eat_time = ft_milisec(0);
	philo->eat_count += 1;//dead fonksiyonuna bağlı olarak burada kontrol edilebilir.
	if (ft_print("is eating", philo))
		return (0);
	usleep(philo->data->time_eat * 1000);
	return (1);
}

void	*ft_thread_function(void *arg)
{
	t_philo *philo;

	philo = arg;
		getchar();
	while (1)
	{
		if (!ft_eat(philo))
			break ;
		if (!ft_print("is Slepping", philo))
			break ;
		usleep(philo->data->time_sleep * 1000);
		if (!ft_print("is Thinking", philo))
			break ;
	}
	return (0);
}
