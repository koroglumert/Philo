/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:44:13 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/19 16:55:17 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				is_dead;
	pthread_t		id_dead_thread;
	long long		start_time;
	pthread_mutex_t printing;
	pthread_mutex_t data_race;
}	t_data;

typedef struct s_philo
{
	pthread_t		id_thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				id_philo;
	int				eat_count;
	long long		last_eat_time;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

int			ft_argument_check(int argc, char **argv, t_data *data);
int			ft_mutex_init(t_data *data, pthread_mutex_t	**forks);
void		ft_destroy_mutex(t_data *data, pthread_mutex_t *forks);
void		*ft_thread(void *philo);
void		ft_create_join_threads(t_philo *philos);
long long	ft_milisec(long long first);
int			ft_fork_mutex_unlock(t_philo *philo);

#endif
