/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 22:05:33 by aderraj           #+#    #+#             */
/*   Updated: 2024/09/01 10:31:42 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    philo_sleep(t_philo *philo)
{
    printf("%ldms philo %d is sleeping\n",get_timestamp() - philo->info->start_time, philo->philo_no);
    usleep(philo->info->time_to_sleep * 1000);
}

void   eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->forks[philo->philo_no % philo->info->num_of_philos]);
    printf("%ldms philo %d has taken a fork\n",get_timestamp() - philo->info->start_time, philo->philo_no);
    pthread_mutex_lock(&philo->info->forks[philo->philo_no - 1]);
    printf("%ldms philo %d has taken a fork\n", get_timestamp() - philo->info->start_time, philo->philo_no);
    printf("%ldms philo %d is eating\n", get_timestamp() - philo->info->start_time, philo->philo_no);
    usleep(philo->info->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->info->forks[philo->philo_no - 1]);
    pthread_mutex_unlock(&philo->info->forks[philo->philo_no % philo->info->num_of_philos]);
}

void    think(t_philo *philo)
{
    printf("%ldms philo %d is thinking\n",get_timestamp() - philo->info->start_time, philo->philo_no);
    usleep(10);
}
