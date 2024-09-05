/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/05 14:55:27 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    printf("%ld %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(philo->info->time_to_sleep * 1000);
}

void   eat(t_philo *philo)
{
    if (!philo->fork->status == 0 && !philo->fork[(philo->id - 1) % philo->info->num_of_philos].status)
    {
        pthread_mutex_lock(&philo->fork->mtx);
        pthread_mutex_unlock(&philo->fork->mtx);
    }
}

void    think(t_philo *philo)
{
    printf("%ld %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(10);
}
