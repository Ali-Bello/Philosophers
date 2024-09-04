/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/04 14:31:29 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    printf("%ldms philo %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(philo->info->time_to_sleep * 1000);
}

void   eat(t_philo *philo)
{
    pthread_mutex_t *fork_1;
    pthread_mutex_t *fork_2;

    fork_1 = philo->r_fork;
    fork_2 = philo->l_fork;
    if (philo->id % 2 == 0)
    {
        fork_1 = philo->l_fork;
        fork_2 = philo->r_fork;
    }
    pthread_mutex_lock(fork_1);
    printf("%ldms philo %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
    printf("%ldms philo %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
    pthread_mutex_lock(fork_2);
    printf("%ldms philo %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->id);
    printf("%ldms philo %d is eating\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(fork_2);
    pthread_mutex_lock(fork_1);
}

void    think(t_philo *philo)
{
    printf("%ldms philo %d is thinking\n",get_timestamp() - philo->info->start_time, philo->id);
    usleep(10);
}
