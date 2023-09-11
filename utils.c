/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:40:11 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/12 00:40:14 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	ft_milisec(long long first)
{
	struct timeval	tv;
	long long	rtn;

	gettimeofday(&tv, NULL);
	rtn = (tv.tv_sec * 1000) + (tv.tv_usec / 1000)  - first;
	return (rtn);
}
