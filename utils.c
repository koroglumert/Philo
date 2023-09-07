/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:29:41 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/06 17:29:00 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long	ft_milisec(long first)
{
	struct timeval	tv;
	long	rtn;

	gettimeofday(&tv, NULL);
	rtn = (long)((tv.tv_sec) / 1000);
	return (rtn - first);
}
